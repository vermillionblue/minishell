/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:28:57 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/14 21:22:56 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// - memory leaks
// - fd leaks
// - norminette
// - parenthesis 
// - <in cat -e | wc >>out /// apparently one fd leak
// convert **cmds to *cmds for *line in ft_subshell
//  �2��PV: No such file or directory fix , in set i o
// 

int	if_omit_space(char *line);
int	ft_isspace(char c);

char *split_rev(char **cmds)
{
	int		i;
	char	*line;
	char	*temp;

	i = 1;
	temp = cmds[0];
	while (cmds[i])
	{
		line = ft_strjoin(temp, cmds[i]);
		i++;
	}
	if (i == 1)
		return (temp);
	return (line);
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
		while (!msh.exit)
		{
			env_list = create_env_list(envp);
			ft_init_delims(&msh);
			ft_signal_parent();
			msh.exit = 0;
			if (!line)
			{
				ft_putchar_fd('\n', STDOUT_FILENO);
				exit(EXIT_SUCCESS);
			}
			if (if_omit_space(line))
				continue ;
			add_history(line);
			ft_lexer(line, &msh);
			ft_printlexems(msh.lexems);
			ft_makegroups(&msh);
			ft_prep_exec(&msh, &env_list);
			free(line);
		}
	}
	waitpid(0, &res, 0);
	return (res);
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\n'
		|| c == '\r')
			return (1);
	return (0);
}

int	if_omit_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
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
	msh.exit = 0;
	while (!msh.exit)
	{
		line = readline("\033[0;35mminishell 🦄$ \033[0;37m");
		if (!line)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		if (if_omit_space(line))
			continue ;
		add_history(line);
		ft_lexer(line, &msh);
		ft_printlexems(msh.lexems);
		ft_makegroups(&msh);
		ft_prep_exec(&msh, &env_list);
		free(line);
	}
	do_exit();
	return (0);
}
