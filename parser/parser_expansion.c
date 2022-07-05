/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:10:15 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/05 17:27:53 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_expand_all_groups_vars(t_msh *msh)
{
	int	i;

	i = 0;
	while (i < msh->group_num)
	{
		ft_expand_group_vars(msh, i);
	}
}

void	ft_expand_group_vars(t_msh *msh, int group_i)
{
	t_list	*link;
	t_list	*next;
	t_env	*var;
	char	*text;

	link = *msh->groups[group_i]->lexems;
	while(link)
	{
		next = link->next;
		if (ft_ectracttype(link) == LX_VAR)
		{
			text = (*(t_lexem *)link->content).text;
			printf("TEST text: %s\n", text);
			var = find_env_node(&(msh->env_list), text);
			if (var)
			{
				(*(t_lexem *)link->content).text = var->bash_v_content;
				printf("TEST new text: %s\n", (*(t_lexem *)link->content).text);
				// free(text);
				// free(value);
				(*(t_lexem *)link->content).type = LX_WORD;
			}
			else
			{
				ft_lst_detach_from(msh->groups[group_i]->lexems, link);
				// free((*(t_lexem *)link->content).text);
				// free(link);
			}
		}
		link = next;
	}
}
