# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/29 14:19:05 by danisanc          #+#    #+#              #
#    Updated: 2022/06/24 16:08:54 by danisanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c builtins/cd.c temporal.c builtins/export.c builtins/pwd.c \
builtins/exit.c builtins/unset.c builtins/env.c builtins/export_sort.c \
exec/exec.c signals.c builtins/echo.c

OBJ = $(SRC:.c=.o)

CC = gcc

UNAME_S := $(shell uname -s)

LIB_MAC =  -I $(HOME)/goinfre/.brew/opt/readline/include/ -lreadline

LIB_LINUX = -lreadline

CFLAGS = -Wall -Werror -Wextra -I includes/ -g

RM = rm -f

all: $(NAME)

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJ)
ifeq ($(UNAME_S), Darwin)
#	$(MAKE) -C libft
	@echo "\033[0;35mCompiling..." 
	@make -C libft
	$(CC) $(OBJ) libft/libft.a  -I/include/ $(LIB_MAC) -o $(NAME)
	@echo "\033[0;37m"
else
	@echo "\033[0;35mCompiling..." 
	@make -C libft
	$(CC) $(OBJ) libft/libft.a $(LIB_LINUX) -o $(NAME)
	@echo "\033[0;37m"
endif

clean:
	$(RM) *.o
	$(RM) builtins/*.o
	$(RM) exec/*.o
	$(RM) libft/*.o

fclean: clean
	$(RM) $(NAME)
	$(RM) libft/libft.a

re: fclean all

.PHONY: all bonus clean fclean re
