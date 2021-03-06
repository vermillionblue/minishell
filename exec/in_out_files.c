/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:09:55 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/13 18:40:14 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	check_infile(t_group *group, t_msh *msh, int j)
{
	char	*limiter;

	limiter = ft_strdup(ft_ectracttext(group->cmds->redirs[j][0]));
	if (ft_ectracttype(group->cmds->redirs[j][0]) == LX_REDIR_INSRC)
	{
		group->cmds->here_doc = 1;
		read_stdin(limiter, msh->here_doc_file_name);
		group->cmds->infile_name = msh->here_doc_file_name;
	}	
	else if (ft_ectracttype(group->cmds->redirs[j][0]) == LX_REDIR_IN)
	{
		group->cmds->here_doc = 0;
		group->cmds->infile_name = \
		ft_ectracttext(group->cmds->redirs[j][0]);
	}
	else
		group->cmds->infile_name = NULL;
}

void	check_outfile(t_group *group, int j)
{
	if (ft_ectracttype(group->cmds->redirs[j][0]) == LX_REDIR_OUT
		|| ft_ectracttype(group->cmds->redirs[j][0]) == LX_REDIR_APPEND)
	{
		group->cmds->outfile_name = ft_ectracttext(group->cmds->redirs[j][0]);
		if (ft_ectracttype(group->cmds->redirs[j][0]) == LX_REDIR_APPEND)
			group->cmds->append_outfile = 1;
		else
			group->cmds->append_outfile = 0;
	}
	else
		group->cmds->outfile_name = NULL;
}
