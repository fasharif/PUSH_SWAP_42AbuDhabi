/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:56:38 by fasharif          #+#    #+#             */
/*   Updated: 2023/06/08 03:06:40 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	check_if_sort(int *tab, int len)
{
	int	i;

	i = 0;
	while (i <= len - 1)
	{
		if (tab[i] < tab[i + 1])
			return (0);
		i++;
	}
	return (1);
}

static char	**split_args(char **av)
{
	char	*joined;
	char	**tab;
	int		i;

	joined = NULL;
	i = 1;
	while (av[i])
	{
		joined = ft_strjoin(joined, av[i++]);
		joined = ft_strjoin(joined, " ");
	}
	tab = ft_split(joined, ' ');
	free(joined);
	return (tab);
}

int	parcing(t_node *node, char **av)
{
	char	**tab;
	int		*tmp;
	int		count;
	int		i;

	tab = split_args(av);
	count = 0;
	while (tab && tab[count])
		count++;
	if (count == 0)
		my_exit("Error\n");
	tmp = (int *)malloc(count * sizeof(int));
	if (!tmp)
		exit(1);
	put_to_tmp(tab, tmp);
	if_has_deplcate(tmp, count);
	node->a = tab_index(tmp, count);
	inverse_tab(node, count);
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (count);
}
