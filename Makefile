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

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = mandatory/main.c mandatory/check_arg.c mandatory/index_pushb.c \
	mandatory/sort_fct.c mandatory/sort_fct_r.c mandatory/sort_small.c \
	mandatory/util_2.c mandatory/utils.c mandatory/utils_3.c

SRC_B = bonus/checker.c bonus/split.c bonus/bonus_sort1.c bonus/bonus_sort2.c \
	bonus/bonus_sort3.c bonus/bonus_utils.c bonus/bonus_utils2.c \
	bonus/bonus_utils3.c bonus/bonus_utils4.c

OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(NAME)

bonus: $(NAME_B)

$(NAME_B): $(OBJ_B)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_B) -o $(NAME_B)

mandatory/%.o: mandatory/%.c mandatory/push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c bonus/push_swap_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

test: all bonus
	python3 tests/test_push_swap.py

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME) $(NAME_B)

re: fclean all

.PHONY: all bonus test clean fclean re
