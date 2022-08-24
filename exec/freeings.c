/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:49:42 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 14:47:16 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	ft_execve(char **cmd, t_msh *msh)
{
	char	*a_path;

	a_path = get_correct_path(cmd, msh);
	if (execve(a_path, cmd, msh->env) == -1)
	{
		perror("execve error\n");
		free(a_path);
		ft_free_exec(msh);
		exit (EXIT_FAILURE);
	}
}

void	ft_free_exec(t_msh *msh)
{
	free(msh->pipe_fds);
	free(msh->temp_i_o);
	free(msh->delims);
	free_env_list(msh->env_list);
	if (msh->paths)
		free_double(msh->paths);
	free_double(msh->env);
	ft_free_msh(msh);
}

void	free_env_list(t_env **env_list)
{
	t_env	*next;

	while (*env_list)
	{
		next = (*env_list)->next;
		free((*env_list)->bash_v_content);
		free((*env_list)->bash_variable);
		free(*env_list);
		*env_list = next;
	}
	free(next);
}
