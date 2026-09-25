/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:56:31 by fasharif          #+#    #+#             */
/*   Updated: 2023/06/08 01:56:33 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	inverse_tab(t_node *node, int count)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = count - 1;
	while (i < j)
	{
		tmp = node->a[i];
		node->a[i] = node->a[j];
		node->a[j] = tmp;
		i++;
		j--;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((int)s1[i] - (int)s2[i]);
}

long long	ft_atoi(char *str)
{
	int			i;
	long long	r;
	long long	k;

	i = 0;
	r = 0;
	k = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (r <= 2147483648LL)
			r = (r * 10) + ((long long)str[i] - 48);
		i++;
	}
	return (r * k);
}

void	if_has_deplcate(int *tmp, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (tmp[i] == tmp[j])
				my_exit("Error\n");
			j++;
		}
		i++;
	}
}
