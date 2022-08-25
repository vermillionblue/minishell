/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:11:08 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/25 17:36:22 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_data(t_msh *msh)
{
	ft_init_delims(msh);
	ft_signal_parent();
	msh->exit = 0;
	msh->last_exit_stat = 0;
	msh->paths = NULL;
}

void	process_cmds_subshell(char *line, t_msh msh)
{
	ft_lexer(line, &msh);
	ft_makegroups(&msh);
	ft_prep_exec(&msh);
	free_double(msh.env);
	ft_free_msh(&msh);
	exit (EXIT_SUCCESS);
}

int	ft_subshell(char *line, char **envp)
{
	t_env	*env_list;
	t_msh	msh;
	int		id;
	int		res;

	id = fork();
	if (id == 0)
	{
		env_list = create_env_list(envp);
		msh.env_list = &env_list;
		init_data(&msh);
		if (!line)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		process_cmds_subshell(line, msh);
	}
	waitpid(0, &res, 0);
	return (res);
}

int	process_cmds(char *line, t_msh *msh)
{
	if (if_omit_space(line))
		return (1);
	add_history(line);
	ft_lexer(line, msh);
	free(line);
	if (ft_makegroups(msh) <= 0)
		return (1);
	ft_prep_exec(msh);
	free_double(msh->env);
	ft_free_msh(msh);
	return (0);
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
	init_data(&msh);
	while (!msh.exit)
	{
		line = readline("\033[0;35mminishell 🦄$ \033[0;37m");
		if (!line)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			break ;
		}
		process_cmds(line, &msh);
	}
	free_env_list(msh.env_list);
	free(msh.delims);
	do_exit();
	return (0);
}
