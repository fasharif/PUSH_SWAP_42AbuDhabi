# push_swap

[![CI](https://github.com/fasharif/PUSH_SWAP_42AbuDhabi/actions/workflows/ci.yml/badge.svg)](https://github.com/fasharif/PUSH_SWAP_42AbuDhabi/actions/workflows/ci.yml)

Sorts a list of integers using two stacks and a fixed set of 11 instructions, and prints the
instructions it used, aiming for as few as possible. Written in C for the 42 Abu Dhabi
curriculum, together with `checker`, which reads a list of instructions and says whether it sorts
the numbers.

```bash
make && make bonus
./push_swap 5 2 8 -1 3 | ./checker 5 2 8 -1 3    # prints OK
./push_swap 5 2 8 -1 3 | wc -l                   # how many instructions it needed
```

## The rules

Stack A starts with the numbers, first argument on top, and stack B starts empty. The goal is to
finish with A sorted, smallest on top, and B empty.

| Instruction | Effect |
| --- | --- |
| `sa`, `sb`, `ss` | Swap the top two elements of A, of B, or of both |
| `pa`, `pb` | Move the top element of B onto A, or of A onto B |
| `ra`, `rb`, `rr` | Rotate up: the top element goes to the bottom |
| `rra`, `rrb`, `rrr` | Rotate down: the bottom element comes to the top |

## How it sorts

1. **Read and check the input.** All arguments are joined and split on spaces, so
   `./push_swap "3 2 1"` works too. Every value must be an integer within `int` range, with no
   duplicates; otherwise the program prints `Error` on standard error and exits with status 1.
2. **Replace each number with its rank** (0 for the smallest), so the rest of the program works
   with 0 to n − 1 whatever the input values are.
3. **2 or 3 numbers:** swap and reverse-rotate until sorted.
4. **4 or 5 numbers:** move the smallest one or two to B, rotating whichever way is shorter, sort
   the three left in A, then push them back.
5. **6 numbers or more, in chunks:**
   - Push ranks to B in chunks of n/10 + 10, lowest chunk first, rotating A until its top belongs
     to the current chunk. Ranks in the lower half of a chunk are rotated to the bottom of B, so B
     ends up roughly ordered around its middle.
   - Then, until B is empty, bring the largest rank in B to the top, rotating the shorter way, and
     push it onto A. A fills from the largest number down and finishes sorted.

## Results

Measured by the tests in CI: every possible ordering of 2 to 5 numbers, and random inputs of 100
and 500 numbers. The random seed is fixed, so these numbers are reproducible.

| Numbers | Inputs tested | Fewest | Average | Most | 42's target |
| ---: | ---: | ---: | ---: | ---: | :--- |
| 2 | 2 | 0 | 0 | 1 | |
| 3 | 6 | 0 | 2 | 3 | At most 3 ✓ |
| 4 | 24 | 0 | 4 | 7 | |
| 5 | 120 | 0 | 8 | 11 | At most 12 ✓ |
| 100 | 50 | 614 | 654 | 698 | Under 700 for full marks ✓ |
| 500 | 20 | 5,589 | 5,772 | 5,977 | Under 5,500 for full marks ✗ (under 7,000 scores 4 of 5) |

## Build and run

```bash
make            # push_swap
make bonus      # checker
./push_swap 3 2 1
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
```

`checker` takes the same numbers as `push_swap`, reads instructions from standard input one per
line, and prints `OK` if they leave A sorted and B empty, or `KO` otherwise. An unknown instruction
or invalid input prints `Error` on standard error.

## Testing

```bash
make test       # builds both programs and runs tests/test_push_swap.py
```

The tests judge `push_swap`'s output with their own stack simulator rather than with `checker`, so
a bug in one program cannot hide a bug in the other. They cover every ordering of 2 to 5 numbers,
random sets of 100 and 500, invalid input (text, duplicates, values outside `int` range, empty
arguments) and input that needs no sorting. `checker` is tested against the same simulator,
including on `push_swap`'s output cut short. GitHub Actions builds with GCC and Clang with warnings
treated as errors, repeats the tests under AddressSanitizer and UndefinedBehaviorSanitizer, and
writes the table above into each run's summary.

## Limitations

- 500 numbers take about 5% more instructions than 42's full-marks target. Choosing each push by
  counting the rotations it costs, instead of working through fixed chunks, would close that gap.
- Both programs exit without freeing all of their memory. The sanitizer job checks for memory
  errors such as overflows, not for leaks.

## Credits

Instruction counts were checked during development with
[lmalki-h/push_swap_tester](https://github.com/lmalki-h/push_swap_tester).
