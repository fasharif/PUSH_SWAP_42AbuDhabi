/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:56:57 by fasharif          #+#    #+#             */
/*   Updated: 2023/06/08 01:56:59 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

typedef struct node
{
	int	*a;
	int	*b;
	int	*top_a;
	int	*top_b;
}	t_node;

void		ft_putstr(char *s);
int			ft_strlen(char *p);
long long	ft_atoi(char *str);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split(char *s, char c);
int			ft_strcmp(char *s1, char *s2);
void		my_exit(char *str);
int			not_long(char *str);
void		put_to_tmp(char **tab, int *tmp);
void		if_has_deplcate(int *tmp, int count);
int			*tab_index(int *tab, int len);
void		inverse_tab(t_node *node, int count);
int			parcing(t_node *node, char **av);
int			check_if_sort(int *tab, int len);
void		sa(int *tab, int len);
void		sb(int *b, int len);
void		ss(int *a, int *b, int top_a, int top_b);
void		pa(int *a, int *b, int *top_a, int *top_b);
void		pb(int *a, int *b, int *top_a, int *top_b);
void		ra(int *a, int top_a);
void		rb(int *b, int top_b);
void		rr(int *a, int *b, int top_a, int top_b);
void		rra(int *a, int top_a);
void		rrb(int *b, int top_b);
void		rrr(int *a, int *b, int top_a, int top_b);

#endif
