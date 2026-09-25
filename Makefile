# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 01:49:56 by fasharif          #+#    #+#              #
#    Updated: 2023/06/08 02:38:52 by fasharif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

NAME_B = checker

src = mandatory/utils.c mandatory/sort_fct_r.c mandatory/sort_fct.c\
		mandatory/main.c mandatory/check_arg.c mandatory/index_pushb.c\
		mandatory/sort_small.c mandatory/util_2.c mandatory/utils_3.c

src_b = bonus/bonus_sort1.c bonus/checker.c bonus/bonus_sort2.c\
		bonus/bonus_sort3.c bonus/bonus_utils.c  bonus/bonus_utils2.c\
		bonus/bonus_utils3.c bonus/bonus_utils4.c bonus/split.c

obj = $(src:.c=.o)

obj_b = $(src_b:.c=.o)

flags = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(src) $(obj) mandatory/push_swap.h
	@gcc $(flags) $(src) -o $(NAME)
	@echo ------Compiled Mondatory part-------


bonus: $(NAME_B)

$(NAME_B): $(src_b) $(obj_b) bonus/push_swap_bonus.h
	@gcc $(flags) $(src_b) -o $(NAME_B)
	@echo ------Compiled Bonus part-------

%.o: %.c
	@gcc -c $< -o $@
	@echo ------Compiling Objects files-------

clean:
	@rm -rf $(obj) $(obj_b)
	@echo ------Deleting Objects Files-------

fclean: clean
	@rm -rf $(NAME) $(NAME_B)
	@echo ------Deleting Output Files-------

re: fclean all
	