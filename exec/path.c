/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:03:15 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 14:13:10 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	*get_correct_path(char **cmd, t_msh *msh)
{
	int		i;
	char	*a_path;
	char	*temp;

	i = 0;
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) == 0)
			return (cmd[0]);
		else
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			msh->last_exit_stat = 127;
			exit (EXIT_FAILURE);
		}
	}
	while (msh->paths != NULL && msh->paths[i])
	{
		temp = ft_strjoin(msh->paths[i], "/");
		a_path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (access(a_path, F_OK) == 0)
			return (a_path);
		free(a_path);
		i++;
	}
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free_exec(msh);
	msh->last_exit_stat = 127;
	exit (EXIT_FAILURE);
}

char	**get_paths(char **env)
{
	int		i;
	char	**temp;
	char	*env_temp;

	i = 0;
	temp = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			env_temp = ft_strdup(env[i] + 5);
			temp = ft_split(env_temp, ':');
			free(env_temp);
			return (temp);
		}
		i++;
	}
	if (temp)
		free_double(temp);
	return (NULL);
}
