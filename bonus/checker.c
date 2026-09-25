/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:56:49 by fasharif          #+#    #+#             */
/*   Updated: 2023/06/08 02:59:27 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

/*
** Reads one instruction from standard input into line (at most 3 characters).
** Returns 1 when a line was read and 0 at the end of the input.
*/
static int	read_instruction(char *line)
{
	int		len;
	char	c;

	len = 0;
	if (read(0, &c, 1) <= 0)
		return (0);
	while (c != '\n')
	{
		if (len == 3)
			my_exit("Error\n");
		line[len++] = c;
		if (read(0, &c, 1) <= 0)
			break ;
	}
	line[len] = '\0';
	return (1);
}

static void	apply_reverse(t_node *n, char *op)
{
	if (ft_strcmp(op, "rra") == 0)
		rra(n->a, *n->top_a);
	else if (ft_strcmp(op, "rrb") == 0)
		rrb(n->b, *n->top_b);
	else if (ft_strcmp(op, "rrr") == 0)
		rrr(n->a, n->b, *n->top_a, *n->top_b);
	else
		my_exit("Error\n");
}

static void	apply(t_node *n, char *op)
{
	if (ft_strcmp(op, "sa") == 0)
		sa(n->a, *n->top_a + 1);
	else if (ft_strcmp(op, "sb") == 0)
		sb(n->b, *n->top_b + 1);
	else if (ft_strcmp(op, "ss") == 0)
		ss(n->a, n->b, *n->top_a, *n->top_b);
	else if (ft_strcmp(op, "pa") == 0)
		pa(n->a, n->b, n->top_a, n->top_b);
	else if (ft_strcmp(op, "pb") == 0)
		pb(n->a, n->b, n->top_a, n->top_b);
	else if (ft_strcmp(op, "ra") == 0)
		ra(n->a, *n->top_a);
	else if (ft_strcmp(op, "rb") == 0)
		rb(n->b, *n->top_b);
	else if (ft_strcmp(op, "rr") == 0)
		rr(n->a, n->b, *n->top_a, *n->top_b);
	else
		apply_reverse(n, op);
}

static void	run_checker(t_node *node)
{
	char	line[4];

	while (read_instruction(line))
		apply(node, line);
	if (*node->top_b == -1 && check_if_sort(node->a, *node->top_a))
		ft_putstr("OK\n");
	else
		ft_putstr("KO\n");
}

int	main(int ac, char **av)
{
	t_node	node;
	int		top_a;
	int		top_b;
	int		count;

	if (ac < 2)
		return (0);
	count = parcing(&node, av);
	node.b = (int *)malloc(sizeof(int) * count);
	if (!node.b)
		return (1);
	top_a = count - 1;
	top_b = -1;
	node.top_a = &top_a;
	node.top_b = &top_b;
	run_checker(&node);
	free(node.a);
	free(node.b);
	return (0);
}
