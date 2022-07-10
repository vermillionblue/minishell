/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/10 22:22:23 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int	if_omit_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env_list;
	t_msh	msh;

	(void) argc;
	(void) argv;
	
	env_list = create_env_list(envp);
	ft_init_delims(&msh);
	ft_signal_parent();
	while(1)
	{
		env_list = create_env_list(envp);
		msh.env_list = &env_list; // printf("TEST PATH: %s\n", find_env_node(&msh.env_list, "PATH")->bash_v_content);
		//env_list = create_env_list(envp);
		line = readline("\033[0;35mminishell 🦄$ \033[0;37m");
		if (!line)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			exit(EXIT_SUCCESS) ;
		}
		if (if_omit_space(line))
			continue ;
		add_history(line);
		ft_lexer(line, &msh);
		
		ft_printlexems(msh.lexems);
		ft_parser(&msh);
		
		ft_print_groups(&msh);
		ft_prep_exec(&msh, &env_list);
		free(line);
	}
	return (0);
}
