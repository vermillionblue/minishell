/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:03:15 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/12 21:46:16 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	*get_correct_path(char **cmd, t_msh *msh)
{
	int		i;
	char	*a_path;
	char	*temp;

	i = 0;
	if (access(cmd[0], F_OK) == 0)
		return (cmd[0]);
	while (msh->paths != NULL && msh->paths[i])
	{
		temp = ft_strjoin(msh->paths[i], "/");
		a_path = ft_strjoin(temp, cmd[0]);
		if (access(a_path, F_OK) == 0)
			return (a_path);
		i++;
	}
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	msh->last_exit_stat = 127;
	exit (EXIT_FAILURE);
}

char	**get_paths(char **env, t_msh *msh)
{
	int		i;
	char	**temp;

	i = 0;
	(void)msh;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{	
			ft_memmove(env[i], env[i] + 5, ft_strlen(env[i]));
			temp = ft_split(env[i], ':');
			return (temp);
		}
		i++;
	}
	return (NULL);
}
