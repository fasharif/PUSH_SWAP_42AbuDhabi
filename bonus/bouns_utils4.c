/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bouns_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:56:38 by fasharif          #+#    #+#             */
/*   Updated: 2023/06/08 03:06:40 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	ko(void)
{
	write(1, "ko\n", 3);
	exit (1);
}

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

void	parcing(t_node *node, char **av, int ac)
{
	int		i;
	char	*ptr;
	char	**tab;
	int		*tmp;

	if (ac < 2)
		my_exit("");
	if_av_has_alpha(av);
	i = 1;
	ptr = NULL;
	while (av[i])
	{
		ptr = ft_strjoin(ptr, av[i]);
		ptr = ft_strjoin(ptr, " ");
		i++;
	}
	tab = ft_split(ptr, ' ');
	tmp = (int *)malloc((ac - 1) * sizeof(int));
	if (!tmp)
		exit (1);
	put_to_tmp(tab, tmp);
	if_has_deplcate(tmp, ac);
	node->a = tab_index(tmp, ac -1);
	inverse_tab(node, ac);
}
