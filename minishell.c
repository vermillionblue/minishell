/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:11:08 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 12:53:43 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/minishell.h"

// - memory leaks
// - fd leaks
// - norminette
// - parenthesis 
// - ls *.o not working


void	free_env_arr(char **arr)
{
	int i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
void	free_env_list(t_env **env_list)
{
	t_env	*next;

	while(*env_list)
	{
		next = (*env_list)->next;
		free((*env_list)->bash_v_content);
		free((*env_list)->bash_variable);
		free(*env_list);
		*env_list = next;
	}
	free(next);
}

void	free_exec(t_msh *msh)
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
		env_list = create_env_list(envp);
		msh.env_list = &env_list;
		while (!msh.exit)
		{
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
			//ft_prep_exec(&msh);
			free(line);
			free_double(msh.env);
			free(msh.pipe_fds);
			free(msh.temp_i_o);
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
		ft_parser(&msh);
		//ft_print_groups(&msh);
		ft_prep_exec(&msh);
		free(line);
		free_double(msh.env); 
		ft_free_msh(&msh);
	}
	//free_exec(&msh);
	//free_double(msh.paths);
	free_env_list(msh.env_list);
	free(msh.delims);
	// free_double(msh.env);
	//ft_free_groups(&msh);
	// ft_free_msh(&msh);
	do_exit();
	return (0);
}
