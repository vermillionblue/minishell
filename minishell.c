/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/11 19:31:35 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// //todo
// - memory leaks
// - fd leaks
// - history 
// - norminette
// - exit correctly (the only cmd in line , and group?)
// - parenthesis 
// - clean here doc
// - unset path && ls does not work!
// - dup error with pipes, specifically with: env | grep PATH

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
		//ft_add_history();
		ft_lexer(line, &msh);
		ft_printlexems(msh.lexems);
		ft_print_groups(&msh);
		ft_prep_exec(&msh, &env_list);
		free(line);
	}
	return (0);
}
