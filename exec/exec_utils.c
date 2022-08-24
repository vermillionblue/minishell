/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:39:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 08:30:06 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	builtin_or_exec(t_group *group, t_msh *msh, int cmd_num, int j)
{
	int	res;

	if_redirs_or_null(group, msh, j);
	res = redirect_parent(group->cmds->newargvs[j], cmd_num, msh);
	if (res == -2)
	{
		msh->last_exit_stat = exec_cmds(group->cmds->newargvs[j],
			group, msh, cmd_num);
	}	
	else
		msh->last_exit_stat = res;
}

void	if_redirs_or_null(t_group *group, t_msh *msh, int j)
{
	group->cmds->here_doc = 0;
	group->cmds->infile_name = NULL;
	group->cmds->outfile_name = NULL;
	if (group->cmds->redirs[j][0])
		check_what_redirs(group, msh, j);
}

void	check_what_redirs(t_group *group, t_msh *msh, int j)
{
	t_list*	link;

	link = group->cmds->redirs[j][0];
	while (link)
	{
		check_infile(group, msh, j);
		check_outfile(group, j);
		link = link->next;
	}
}

void	init_data4group(t_msh *msh)
{
	msh->temp_i_o = ft_calloc(2, sizeof(int));
	check_dup(msh->temp_i_o[READ_END] = dup(STDIN_FILENO));
	check_dup(msh->temp_i_o[WRITE_END] = dup(STDOUT_FILENO));
}
