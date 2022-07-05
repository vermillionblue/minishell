# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/29 14:19:05 by danisanc          #+#    #+#              #
#    Updated: 2022/07/05 13:05:10 by danisanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c builtins/cd.c temporal.c builtins/export.c builtins/pwd.c \
builtins/exit.c builtins/unset.c builtins/env.c builtins/export_sort.c \
exec/exec.c signals.c builtins/echo.c asterisk.c parser/lexer.c parser/lists.c parser/parser.c parser/parser_redirs.c parser/printer.c

OBJ = $(SRC:.c=.o)

CC = gcc

UNAME_S := $(shell uname -s)

LIB_MAC =  -I $(HOME)/goinfre/.brew/opt/readline/include/ -lreadline

LIB_LINUX = -lreadline

CFLAGS = -I includes/ -g

RM = rm -f

all: $(NAME)

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJ)
ifeq ($(UNAME_S), Darwin)
	@echo "\033[0;35mCompiling..." 
	@make bonus -C libft
	@make -C vlad_printf
	$(CC) $(OBJ) libft/libft.a vlad_printf/libftprintf.a -I/include/ $(LIB_MAC) -o $(NAME)
	@echo "\033[0;37m"
else
	@echo "\033[0;35mCompiling..." 
	@make -C vlad_printf
	@make bonus -C libft
	$(CC) $(OBJ) libft/libft.a vlad_printf/libftprintf.a $(LIB_LINUX) -o $(NAME)
	@echo "\033[0;37m"
endif

clean:
	$(RM) *.o
	$(RM) builtins/*.o
	$(RM) exec/*.o
	$(RM) parser/*.o
	$(RM) libft/*.o
	$(RM) vlad_printf/*.o

fclean: clean
	$(RM) $(NAME)
	$(RM) libft/libft.a
	$(RM) vlad_printf/libftprintf.a

re: fclean all

.PHONY: all bonus clean fclean re
