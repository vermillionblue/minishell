/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:39:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/16 12:56:38 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	builtin_or_exec(t_group *group, t_msh *msh, int cmd_num, int j)
{
	int	res;

	if_redirs_or_null(group, msh, j);
	res = redirect_parent(group->cmds->newargvs[j], cmd_num, msh);
	if (res == -2)
		msh->last_exit_stat = exec_cmds(group->cmds->newargvs[j],
				group, msh);
	else
	{
		printf(" exit stat in child %d\n", res);
		msh->last_exit_stat = res;
	}
		
}

void	if_redirs_or_null(t_group *group, t_msh *msh, int j)
{
	if (group->cmds->redirs[j][0])
		check_what_redirs(group, msh, j);
	else
	{
		group->cmds->infile_name = NULL;
		group->cmds->outfile_name = NULL;
	}
}

void	ft_parse_group(t_msh *msh, int group_i)
{
	ft_expand_gr_vars(msh, group_i);
	ft_expand_gr_fields(msh, group_i);
	ft_make_cmd_args(msh->groups[group_i]);
	ft_loop_cmds(msh->groups[group_i], ft_expand_gr_wcs);
	msh->groups[group_i]->cmds->redirs = malloc(sizeof(t_list **) \
	* msh->groups[group_i]->cmds->cmd_num);
	ft_loop_cmds(msh->groups[group_i], ft_init_redirs);
	ft_loop_cmds(msh->groups[group_i], ft_format_redirs);
	ft_unite_texts(msh->groups[group_i]);
	ft_loop_cmds(msh->groups[group_i], ft_extract_redirs);
	ft_make_newargvs(msh->groups[group_i]);
}

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
	msh->temp_i_o = ft_calloc(2, sizeof(int));
	check_dup(msh->temp_i_o[READ_END] = dup(STDIN_FILENO));
	check_dup(msh->temp_i_o[WRITE_END] = dup(STDOUT_FILENO));
}
