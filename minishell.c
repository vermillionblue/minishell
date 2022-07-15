/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:28:57 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/15 11:53:09 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// - memory leaks
// - fd leaks
// - norminette
// - parenthesis 
// redirs are broken :(

void	free_env_list(t_env **env_list)
{
	t_env	*temp;
	t_env	*next;

	temp = *env_list;
	while(temp)
	{
		next = temp->next;
		free(temp->bash_v_content);
		free(temp->bash_variable);
		free(temp);
		temp = next;
	}
}

void	free_all(t_msh *msh)
{
	free_env_list(msh->env_list);
	free_double(msh->env);
	free(msh->pipe_fds);
	free(msh->temp_i_o);
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
		msh.exit = 0;
		while (!msh.exit)
		{
			env_list = create_env_list(envp);
			ft_init_delims(&msh);
			ft_signal_parent();
			if (!line)
			{
				ft_putchar_fd('\n', STDOUT_FILENO);
				exit(EXIT_SUCCESS);
			}
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
	free_all(&msh);
	do_exit();
	return (0);
}
