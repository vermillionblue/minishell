# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/29 14:19:05 by danisanc          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/07/09 17:14:55 by vangirov         ###   ########.fr        #
=======
#    Updated: 2022/07/11 19:30:34 by danisanc         ###   ########.fr        #
>>>>>>> dani
#                                                                              #
# **************************************************************************** #

NAME = minishell

<<<<<<< HEAD
SRC = 	minishell.c \
		builtins/cd.c \
		temporal.c \
		builtins/export.c \
		builtins/pwd.c \
		builtins/exit.c \
		builtins/unset.c \
		builtins/env.c \
		builtins/export_sort.c \
		builtins/echo.c \
		exec/exec.c \
		signals.c \
		wildcard/asterisk.c \
		wildcard/asterisk_utils.c \
		parser/lexer.c \
		parser/lists.c \
		parser/parser_main.c \
		parser/parser_groups.c \
		parser/parser_expansion.c \
		parser/parser_wc.c \
		parser/parser_redirs.c \
		parser/parser_redir_utils.c \
		parser/parser_cmds.c \
		parser/printer.c \
		parser/freeings.c
=======
SRC = minishell.c \
	builtins/cd.c builtins/env_utils.c builtins/export.c builtins/pwd.c \
	builtins/exit.c builtins/unset.c builtins/env.c builtins/export_sort.c \
	builtins/export_utils.c builtins/echo.c \
	exec/exec.c exec/errors.c exec/in_out_files.c exec/path.c exec/here_doc.c\
	wildcard/asterisk.c wildcard/asterisk_utils.c \
	parser/lexer.c parser/lists.c parser/parser.c parser/parser_redirs.c parser/printer.c \
	signals.c \
>>>>>>> dani

OBJ = $(SRC:.c=.o)

CC = gcc

UNAME_S := $(shell uname -s)

LIB_MAC =  -I $(HOME)/goinfre/.brew/opt/readline/include/ -lreadline

LIB_LINUX = -lreadline

CFLAGS = -Wall -Wextra -Werror -I includes/ -g

RM = rm -f

all: $(NAME)

$(%.o): $(%.c)

$(NAME): $(OBJ)
ifeq ($(UNAME_S), Darwin)
	@echo "\033[0;35mCompiling..." 
	@make bonus -C libft
	@make -C vlad_printf
	$(CC) $(OBJ) libft/libft.a vlad_printf/libftprintf.a -I /includes/ $(LIB_MAC) -o $(NAME)
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
