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

src = mondatory/utils.c mondatory/sort_fct_r.c mondatory/sort_fct.c\
		mondatory/main.c mondatory/check_arg.c mondatory/index_pushb.c\
		mondatory/sort_small.c mondatory/util_2.c mondatory/utils_3.c

src_b = bonus/bouns_sort1.c bonus/get_next_line.c bonus/bouns_sort2.c\
		bonus/bouns_sort3.c bonus/bouns_utils.c  bonus/bouns_utils2.c\
		bonus/bouns_utils3.c bonus/bouns_utils4.c bonus/split.c

obj = $(src:.c=.o)

obj_b = $(src_b:.c=.o)

flags = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(src) $(obj) mondatory/push_swap.h
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
	