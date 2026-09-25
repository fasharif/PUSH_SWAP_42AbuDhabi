/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:56:11 by fasharif          #+#    #+#             */
/*   Updated: 2023/06/08 01:56:14 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	j = 0;
	i = -1;
	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 2);
		if (!s1)
			return (NULL);
		s1[0] = ' ';
		s1[1] = '\0';
	}
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	while (s1[++i])
		p[i] = s1[i];
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	free(s1);
	return (p);
}

void	my_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void	put_to_tmp(char **tab, int *tmp)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!not_long(tab[i]))
		{
			free(tab);
			free(tmp);
			my_exit("Error\n");
		}
		tmp[i] = (int)ft_atoi(tab[i]);
		i++;
	}
}

int	*tab_index(int *tab, int len)
{
	int	*arr;
	int	i;
	int	j;
	int	index;

	arr = (int *)malloc(sizeof(int) * len);
	if (!arr)
		return (0);
	i = 0;
	while (i < len)
	{
		j = 0;
		index = 0;
		while (j < len)
		{
			if (tab[i] > tab[j])
				index++;
			j++;
		}
		arr[i] = index;
		i++;
	}
	free(tab);
	return (arr);
}
