/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:37:48 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/21 18:27:44 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parser(t_msh *msh)
{
	int	i;

	if (ft_makegroups(msh) == 0)
	{
		i = 0;
		while (i < msh->group_num)
		{
			ft_parse_group(msh, i);
			i++;
		}
	}
}

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
