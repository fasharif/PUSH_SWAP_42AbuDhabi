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

# include<fcntl.h>
# include<stdlib.h>
# include<unistd.h>
# include <stdio.h>
#include <stdint.h>

typedef struct node
{
	int	*a;
	int	*b;
	int	*top_a;
	int	*top_b;
}	t_node;

int			ft_nbrlen(long long nb);
void		ft_putstr(char *s);
int			ft_strlen(char *p);
long long	ft_atoi(char *str);
char		*ft_strdup(char *s1);
char		*get_next_line(int fd);
char		*ft_strjoin(char *s1, char *s2);
void		parcing(t_node *node, char **av, int ac);
void		my_exit(char *str);
int			has_alpha_2(char *str);
void		if_has_deplcate(int *tmp, int ac);
int			*tab_index(int *tab, int len);
void		put_to_tmp(char **tab, int *tmp);
int			not_long(char *str);
char		**ft_split(char *s, char c);
void		if_av_has_alpha(char **av);
void		inverse_tab(t_node *node, int ac);
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
int			ft_strcmp(char *s1, char *s2);
int			check_if_sort(int *tab, int len);
void		ko(void);
long long	ft_atoi(char *str);

#endif
