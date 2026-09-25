#!/usr/bin/env python3
"""End-to-end tests for push_swap and its checker.

Run from the repository root after building both programs:

    make all bonus && python3 tests/test_push_swap.py

push_swap's output is judged by the simulator below rather than by the checker, so a
bug in one program cannot hide a bug in the other. The checker is tested separately.
Set SEED to try different random inputs; the default makes every run reproducible.
"""

import itertools
import os
import random
import subprocess
import sys

PUSH_SWAP = "./push_swap"
CHECKER = "./checker"
INT_MIN, INT_MAX = -(2**31), 2**31 - 1
INSTRUCTIONS = {"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"}

# 42's targets: at most 3 and 12 instructions for 3 and 5 numbers (required), and fewer
# than 700 and 5500 for 100 and 500 numbers (needed for full marks).
TARGETS = {3: (3, "≤ 3"), 5: (12, "≤ 12"), 100: (699, "< 700"), 500: (5499, "< 5500")}
REQUIRED = {3, 5}

failures = []


def run(program, args, stdin=""):
    """Run a program and return (exit status, stdout, stderr)."""
    done = subprocess.run([program, *args], input=stdin, capture_output=True, text=True, timeout=60)
    return done.returncode, done.stdout, done.stderr


def expect(condition, message):
    if not condition:
        failures.append(message)


def simulate(numbers, instructions):
    """Apply instructions to stack A (numbers[0] on top). Return 'OK', 'KO' or 'Error'."""
    a, b = list(numbers), []
    for op in instructions:
        if op not in INSTRUCTIONS:
            return "Error"
        if op in ("sa", "ss") and len(a) > 1:
            a[0], a[1] = a[1], a[0]
        if op in ("sb", "ss") and len(b) > 1:
            b[0], b[1] = b[1], b[0]
        if op == "pa" and b:
            a.insert(0, b.pop(0))
        if op == "pb" and a:
            b.insert(0, a.pop(0))
        if op in ("ra", "rr") and a:
            a.append(a.pop(0))
        if op in ("rb", "rr") and b:
            b.append(b.pop(0))
        if op in ("rra", "rrr") and a:
            a.insert(0, a.pop())
        if op in ("rrb", "rrr") and b:
            b.insert(0, b.pop())
    return "OK" if not b and a == sorted(a) else "KO"


def sort(numbers):
    """Run push_swap on numbers and return (verdict, number of instructions)."""
    status, out, err = run(PUSH_SWAP, [str(n) for n in numbers])
    if status != 0 or err:
        return f"exit status {status}, stderr {err!r}", 0
    instructions = out.split()
    return simulate(numbers, instructions), len(instructions)


def test_invalid_input():
    cases = [
        ["abc", "5", "3"],  # the first number used to go unchecked
        ["5", "abc", "3"],
        ["12a", "3"],
        ["1", "1"],
        ["2147483648"],
        ["-2147483649"],
        ["99999999999999999999", "1"],
        [""],
        ["-"],
        ["+"],
        ["--5", "1"],
    ]
    for args in cases:
        for program in (PUSH_SWAP, CHECKER):
            status, out, err = run(program, args)
            expect(status == 1 and out == "" and err == "Error\n",
                   f"{program} {args}: expected 'Error' on stderr and exit status 1, "
                   f"got status {status}, stdout {out!r}, stderr {err!r}")


def test_nothing_to_do():
    for args in ([], ["42"], ["1", "2", "3"], ["-7", "0", str(INT_MAX)], [str(INT_MIN), "+5", "007"]):
        status, out, err = run(PUSH_SWAP, args)
        expect(status == 0 and out == "" and err == "",
               f"push_swap {args}: expected no output, got status {status}, "
               f"stdout {out!r}, stderr {err!r}")
    status, out, err = run(CHECKER, [])
    expect(status == 0 and out == "" and err == "",
           f"checker without arguments: expected no output, got status {status}, stdout {out!r}")


def test_quoted_arguments():
    status, out, err = run(PUSH_SWAP, ["4 3 2 1 0"])
    expect(status == 0 and simulate([4, 3, 2, 1, 0], out.split()) == "OK",
           f"push_swap '4 3 2 1 0' did not sort (status {status}, stderr {err!r})")
    status, verdict, err = run(CHECKER, ["4 3 2 1 0"], out)
    expect(verdict == "OK\n",
           f"checker '4 3 2 1 0' on push_swap's output: expected OK, got {verdict!r} {err!r}")


def test_every_small_input(stats):
    """Every ordering of 2 to 5 numbers, including negative ones."""
    for size in range(2, 6):
        counts = []
        for order in itertools.permutations(range(size)):
            numbers = [n * 1000 - 2000 for n in order]
            verdict, count = sort(numbers)
            expect(verdict == "OK", f"push_swap {numbers}: {verdict}")
            counts.append(count)
        stats.append((size, len(counts), min(counts), sum(counts) / len(counts), max(counts)))


def test_random_inputs(stats, rng, size, runs):
    counts = []
    for _ in range(runs):
        numbers = rng.sample(range(INT_MIN, INT_MAX + 1), size)
        verdict, count = sort(numbers)
        expect(verdict == "OK", f"push_swap on {size} random numbers: {verdict}")
        counts.append(count)
    stats.append((size, runs, min(counts), sum(counts) / runs, max(counts)))


def test_checker(rng):
    cases = [
        (["1", "2", "3"], "", "OK\n"),
        (["2", "1", "3"], "sa\n", "OK\n"),
        (["1", "2", "3"], "sa\n", "KO\n"),
        (["3", "1", "2"], "ra\n", "OK\n"),
        (["3 1 2"], "ra\n", "OK\n"),  # several numbers in one argument
        (["1", "2", "3"], "pb\n", "KO\n"),  # stack B must end empty
        (["1", "2", "3"], "pa\n", "OK\n"),  # pa with B empty does nothing
        (["1", "2", "3"], "pb\npb\nrr\nrrr\npa\npa\n", "OK\n"),
        (["2", "1", "3"], "sa", "OK\n"),  # last line without a newline
    ]
    for args, stdin, expected in cases:
        numbers = [int(n) for arg in args for n in arg.split()]
        expect(simulate(numbers, stdin.split()) + "\n" == expected,
               f"test case {args} {stdin!r} disagrees with the simulator")
        status, out, err = run(CHECKER, args, stdin)
        expect((status, out, err) == (0, expected, ""),
               f"checker {args} with {stdin!r}: expected {expected!r}, "
               f"got status {status}, stdout {out!r}, stderr {err!r}")

    for stdin in ("foo\n", "SA\n", "sa \n", "\n", "rrrr\n", "pa\nxx\n"):
        status, out, err = run(CHECKER, ["1", "2", "3"], stdin)
        expect(status == 1 and out == "" and err == "Error\n",
               f"checker with {stdin!r}: expected 'Error' on stderr and exit status 1, "
               f"got status {status}, stdout {out!r}, stderr {err!r}")

    # On push_swap's real output, whole and cut short, the checker must agree with the simulator.
    for size in (3, 5, 100, 500):
        numbers = rng.sample(range(-5000, 5000), size)
        args = [str(n) for n in numbers]
        _, out, _ = run(PUSH_SWAP, args)
        lines = out.splitlines(keepends=True)
        for stdin in (out, "".join(lines[:-1]), "".join(lines[: len(lines) // 2])):
            want = simulate(numbers, stdin.split()) + "\n"
            _, verdict, err = run(CHECKER, args, stdin)
            expect(verdict == want,
                   f"checker on {size} numbers and {len(stdin.split())} instructions: "
                   f"expected {want!r}, got {verdict!r} {err!r}")


def report(stats):
    rows = ["| Numbers | Inputs tested | Fewest | Average | Most | 42 target |",
            "| ---: | ---: | ---: | ---: | ---: | :--- |"]
    for size, runs, fewest, average, most in stats:
        limit, label = TARGETS.get(size, (None, ""))
        mark = "" if limit is None else f"{label} {'✓' if most <= limit else '✗'}"
        rows.append(f"| {size} | {runs} | {fewest} | {average:.0f} | {most} | {mark} |")
    table = "\n".join(rows)
    print(table)
    summary = os.environ.get("GITHUB_STEP_SUMMARY")
    if summary:
        with open(summary, "a", encoding="utf-8") as out:
            out.write("### push_swap instruction counts\n\n" + table + "\n")


def main():
    for stream in (sys.stdout, sys.stderr):
        if hasattr(stream, "reconfigure"):
            stream.reconfigure(encoding="utf-8")
    rng = random.Random(int(os.environ.get("SEED", "2026")))
    stats = []
    test_invalid_input()
    test_nothing_to_do()
    test_quoted_arguments()
    test_every_small_input(stats)
    test_random_inputs(stats, rng, 100, 50)
    test_random_inputs(stats, rng, 500, 20)
    test_checker(rng)
    report(stats)
    for size, _, _, _, most in stats:
        if size in REQUIRED:
            limit = TARGETS[size][0]
            expect(most <= limit,
                   f"sorting {size} numbers took up to {most} instructions; the subject allows {limit}")
    if failures:
        print(f"\n{len(failures)} check(s) failed:", file=sys.stderr)
        for message in failures[:40]:
            print("  - " + message, file=sys.stderr)
        return 1
    print("\nAll checks passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
