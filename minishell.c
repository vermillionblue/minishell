/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:28:57 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/15 01:11:23 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// - memory leaks
// - fd leaks

// - norminette
// - parenthesis 
// - clean here doc
// - unset path && ls does not work!
// - dup error with pipes, specifically with: env | grep PATH
// - change isspace

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
	// env_list = create_env_list(envp);
	ft_init_delims(&msh);
	ft_signal_parent();
	msh.exit = 0;
	while(!msh.exit)
	{
		line = readline("\033[0;35mminishell 🦄$ \033[0;37m");
		if (!line)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			exit(EXIT_SUCCESS) ;
		}
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			break ;
		}
		if (if_omit_space(line))
			continue ;
		add_history(line);
//////////////////////////////////////////////////////////////////////////
		env_list = create_env_list(envp);
		msh.env_list = &env_list; 
		ft_lexer(line, &msh);
		// ft_printlexems(msh.lexems);
		ft_makegroups(&msh);
		ft_parser(&msh); //////////////////////////////// ft_makegroups(msh) // should check if == 0???
		// ft_print_groups(&msh);
		// ft_prep_exec(&msh, &env_list);
		ft_free_msh(&msh);
		free(line);
	}
	do_exit();
	// ft_free_msh(&msh);
	free(msh.delims);
	free(line);
	// exit(0);
	return (0);
}
