/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:59:44 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/25 20:05:31 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	set_up_child(t_group *group, char **cmd, t_msh *msh, int cmd_num)
{
	ft_signal_child();
	close_fds_child(group, msh, cmd_num);
	redirect_child(cmd, msh);
}

void	free_pipes_n_paths(t_msh *msh)
{
	if (msh->paths)
		free_double(msh->paths);
	free(msh->pipe_fds);
}
