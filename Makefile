# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/29 14:19:05 by danisanc          #+#    #+#              #
#    Updated: 2022/08/24 00:18:18 by danisanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
		
SRC = minishell.c \
	builtins/cd.c builtins/env_utils.c builtins/export.c builtins/pwd.c \
	builtins/exit.c builtins/unset.c builtins/env.c builtins/export_sort.c \
	builtins/export_utils.c builtins/echo.c \
	exec/exec.c exec/errors.c exec/in_out_files.c exec/path.c exec/here_doc.c exec/fd_control.c exec/exec_utils.c \
	wildcard/asterisk.c wildcard/asterisk_utils.c \
	42msh_parser/freeings.c \
	42msh_parser/lexer.c \
	42msh_parser/lists.c \
	42msh_parser/parser_cmds.c \
	42msh_parser/parser_expansion.c \
	42msh_parser/parser_groups.c \
	42msh_parser/parser_main.c \
	42msh_parser/parser_redirs.c \
	42msh_parser/parser_redir_utils.c \
	42msh_parser/parser_wc.c \
	42msh_parser/printer.c \
	signals.c \
	utils.c \

OBJ = $(SRC:.c=.o)

CC = gcc

UNAME_S := $(shell uname -s)

LIB_MAC =  -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

LIB_LINUX = -lreadline

LIBS = $(LIB_MAC) -I./includes

ifeq ($(UNAME_S), Darwin)
	CFLAGS =  -Wall -Wextra -Werror -g -I $(HOME)/goinfre/.brew/opt/readline/include/
else
	CFLAGS =  -Wall -Wextra -Werror -g -I includes/
endif

RM = rm -f

all: $(NAME)

$(%.o): $(%.c)

$(NAME): $(OBJ)
ifeq ($(UNAME_S), Darwin)
	@echo "\033[0;35mCompiling..." 
	@make bonus -C libft
	@make -C vlad_printf
	$(CC) $(OBJ) libft/libft.a vlad_printf/libftprintf.a $(LIB_MAC) -o $(NAME)
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
	$(RM) 42msh_parser/*.o
	$(RM) libft/*.o
	$(RM) wildcard/*.o
	$(RM) vlad_printf/*.o

fclean: clean
	$(RM) $(NAME)
	$(RM) libft/libft.a
	$(RM) vlad_printf/libftprintf.a

re: fclean all

.PHONY: all bonus clean fclean re
