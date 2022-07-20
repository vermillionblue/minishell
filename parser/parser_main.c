/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:37:48 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/19 13:35:46 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_parser(t_msh *msh)
// {
// 	int	i;

// 	if (ft_makegroups(msh) == 0)
// 	{
// 		i = 0;
// 		while (i < msh->group_num)
// 		{
// 			ft_expand_gr_vars(msh, i);
// 			ft_expand_gr_fields(msh, i);
// 			ft_make_cmd_args(msh->groups[i]);
// 			ft_loop_cmds(msh->groups[i], ft_expand_gr_wcs);
// 			msh->groups[i]->cmds->redirs = malloc(sizeof(t_list **) 
// 				* msh->groups[i]->cmds->cmd_num);
// 			ft_loop_cmds(msh->groups[i], ft_init_redirs);
// 			ft_loop_cmds(msh->groups[i], ft_format_redirs);
// 			ft_unite_texts(msh->groups[i]);
// 			ft_loop_cmds(msh->groups[i], ft_extract_redirs);
// 			ft_make_newargvs(msh->groups[i]);
// 			i++;
// 		}
// 	}
// }

int	ft_error(char *error_text, int error_num)
{
	ft_fdprintf(2, "minishell: %s (%d)\n", error_text, -error_num);
	return (error_num);
}

int	ft_unite_texts(t_group *group)
{
	int		cmd_i;
	t_list	*link;
	t_list	*next;

	cmd_i = 0;
	while (cmd_i < group->cmds->cmd_num)
	{
		link = *group->cmds->cmd_args[cmd_i];
		while (link)
		{
			if (ft_ectracttype(link) != LX_SEP)
			{
				next = link->next;
				while (next && ft_ectracttype(next) != LX_SEP)
				{
					((t_lexem *)(link->content))->text = 
						ft_strjoin(ft_ectracttext(link), ft_ectracttext(next));
					link->next = next->next;
					free(next->content);
					free(next);
					next = link->next;
				}
			}
			link = link->next;
		}
		cmd_i++;
	}
	return (0);
}
