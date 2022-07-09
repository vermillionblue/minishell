/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:13:32 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/06 21:16:49 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_printlexems(t_list **lexems)
{
	t_list *link;

	link = *lexems;
	while(link)
	{
		if(ft_strlen((*(t_lexem *)link->content).text))
			printf("[%5s]\t\t", (*(t_lexem *)link->content).text);
		else
			printf("       \t\t");
		if ((*(t_lexem *)link->content).type == LX_SEP)
			printf(" SEP \n");
		else
			printf("<%3d>\n", (*(t_lexem *)link->content).type);
		link = link->next;
	}
	printf("============\n");
}

void	ft_print_arg_redir(t_group *group)
{
	for (int j = 0; j < group->cmds->cmd_num; j++)
	{
		printf("command[%d][%d]\n", group->index, j);
		ft_printlexems(group->cmds->cmd_args[j]);
		printf("redirs [%d][%d]\n", group->index, j);
		ft_printlexems(group->cmds->redirs[j]);
	}
}

void    ft_print_newargvs(t_group *group)
{
	for (int j = 0; j < group->cmds->cmd_num; j++)
	{
		for (int k = 0; k < ft_count_args(group->cmds->cmd_args[j]); k++)
		// while (*group->cmds->newargvs[j])
		{
			printf(">>> argv[%d][%d][%d] = %s\n", group->index, j, k, group->cmds->newargvs[j][k]);
		}
	}
}

void ft_print_groups(t_msh *msh)
{
	int i;

	i = 0;
	printf("\n\n\nNUMBER OF GROUPS: %d\n", msh->group_num);
	while(i < msh->group_num)
	{
		printf("============================================\n");
		printf("Group #%d (type %d, cmd_num %d):\n", i, msh->groups[i]->type, msh->groups[i]->cmds->cmd_num);
		ft_print_arg_redir(msh->groups[i]);
		ft_print_newargvs(msh->groups[i]);
		printf("============================================\n");
		i++;
	}
}
