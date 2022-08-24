/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:09:55 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 18:24:38 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	check_infile(t_group *group, t_msh *msh, t_list *link)
{
	char	*limiter;

	if (ft_ectracttype(link) == LX_REDIR_INSRC)
	{
		limiter = ft_strdup(ft_ectracttext(link));
		group->cmds->here_doc = 1;
		read_stdin(limiter, msh->here_doc_file_name);
		group->cmds->infile_name = msh->here_doc_file_name;
	}	
	else if (ft_ectracttype(link) == LX_REDIR_IN)
	{
		group->cmds->infile_name = \
		ft_ectracttext(link);
	}
}

void	check_outfile(t_group *group, t_list *link)
{
	if (ft_ectracttype(link) == LX_REDIR_OUT
		|| ft_ectracttype(link) == LX_REDIR_APPEND)
	{
		group->cmds->outfile_name = ft_ectracttext(link);
		if (ft_ectracttype(link) == LX_REDIR_APPEND)
			group->cmds->append_outfile = 1;
		else
			group->cmds->append_outfile = 0;
	}
}
