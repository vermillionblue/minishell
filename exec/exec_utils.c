/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:39:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/13 20:59:14 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	check_what_redirs(t_group *group, t_msh *msh, int j)
{
	while (group->cmds->redirs[j][0])
	{
		check_infile(group, msh, j);
		check_outfile(group, j);
		group->cmds->redirs[j][0] = group->cmds->redirs[j][0]->next;
	}
}

void	init_data4group(t_msh *msh, t_group *group, int *cmd_num)
{
	*cmd_num = group->cmds->cmd_num;
	msh->temp_i_o = malloc(sizeof(int) * 2);
	check_dup(msh->temp_i_o[READ_END] = dup(STDIN_FILENO));
	check_dup(msh->temp_i_o[WRITE_END] = dup(STDOUT_FILENO));
}
