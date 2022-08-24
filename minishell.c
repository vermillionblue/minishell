/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:11:08 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 18:28:45 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

// - memory leaks
// - fd leaks
// - norminette
// - parenthesis 
// - ls *.o not working

int	ft_subshell(char *line, char **envp)
{
	t_env	*env_list;
	t_msh	msh;
	int		id;
	int		res;

	printf("%s\n", line);
	id = fork();
	if (id == 0)
	{
		env_list = create_env_list(envp);
		msh.env_list = &env_list;
		ft_init_delims(&msh);
		ft_signal_parent();
		msh.exit = 0;
		msh.last_exit_stat = 0;
		if (!line)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		ft_lexer(line, &msh);
		ft_makegroups(&msh);
		ft_prep_exec(&msh);
		free_double(msh.env); 
		ft_free_msh(&msh);
	}
	waitpid(0, &res, 0);
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env_list;
	t_msh	msh;

	(void) argc;
	(void) argv;
	env_list = create_env_list(envp);
	msh.env_list = &env_list;
	ft_init_delims(&msh);
	ft_signal_parent();
	msh.exit = 0;
	msh.last_exit_stat = 0;
	msh.paths = NULL;
	while (!msh.exit)
	{
		line = readline("\033[0;35mminishell 🦄$ \033[0;37m");
		if (!line)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			break ;
		}
		if (if_omit_space(line))
			continue ;
		add_history(line);
		ft_lexer(line, &msh);
		//ft_printlexems(msh.lexems);
		ft_makegroups(&msh);
		ft_prep_exec(&msh);
		//ft_print_groups(&msh);
		free(line);
		free_double(msh.env); 
		ft_free_msh(&msh);
	}
	free_env_list(msh.env_list);
	free(msh.delims);
	do_exit();
	return (0);
}
