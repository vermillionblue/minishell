/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 06:58:08 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/05 18:38:47 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_redir(int type)
{
	if (type == LX_REDIR_OUT || type == LX_REDIR_IN ||
		type == LX_REDIR_APPEND || type == LX_REDIR_INSRC)
		return (type);
	else
		return (-1);
}

void	ft_loop_cmds(t_group *group, void (*opearation)(t_group *, int i))
{
	int	cmd_i;

	cmd_i = 0;
	while(cmd_i < group->cmds->cmd_num)
	{
		opearation(group, cmd_i);
		cmd_i++;
	}
}

void	ft_init_redirs(t_group *group, int cmd_i)
{
		group->cmds->redirs[cmd_i] = malloc(sizeof(t_list *));
		*group->cmds->redirs[cmd_i] = NULL;
}

/*	The function checks if there is anything to redirect after redirection symbol
	and removes all separators between the symbol and the redirection file */
void	ft_format_redirs(t_group *group, int cmd_i)
{
	t_list	*link;
	t_list	*next;
	int		type;

	link = *group->cmds->cmd_args[cmd_i];
	while (link)
	{
		type = ft_ectracttype(link);
		if (ft_is_redir(type) > 0)
		{
			next = link->next;
			if (!next)
			{
				ft_error("No argument after redirection operator [Gr %d, Cmd %d]", \
					-(700 + 10 * group->index + cmd_i));
				return ;
			}
			else if (ft_ectracttype(next) == LX_SEP)
			{
				printf("deleteing SEP\n");
				link->next = next->next;
				printf("TEST <\n");
				ft_free_lexem(next);
			}
		}
		link = link->next;
	}
	// return (0);
}

void	ft_extract_redirs(t_group *group, int cmd_i)
{
	t_list	*link;
	t_list	*temp;

	link = *group->cmds->cmd_args[cmd_i];
	// printf(">>test: %d\n", ft_ectracttype(link));
	while (link)
	{
		// printf("Ed redir\n");
		if (ft_is_redir(ft_ectracttype(link)) > 0)
		{
			temp = link->next;
			ft_lst_detach_from(group->cmds->cmd_args[cmd_i], link);
			ft_lstadd_back(group->cmds->redirs[cmd_i], link);
			link = temp;
			continue;
		}
		link = link->next;
	}
	ft_dellastsep(group->cmds->cmd_args[cmd_i]);
}

// // /* Has to be called after uniting texts */
// int	ft_make_redirs(t_group *group)
// {
// 	int		i;
// 	// t_list	*link;
// 	// t_list	*next;
// 	// int		type;

// 	group->cmds->redirs = malloc(sizeof(t_list **) * group->cmds->cmd_num);
// 	i = 0;
	
// 	while (i < group->cmds->cmd_num)
// 	{
// 		// link = *group->cmds->cmd_args[i];
// 		group->cmds->redirs[i] = malloc(sizeof(t_list *));
// 		*group->cmds->redirs[i] = NULL;
// 		printf(">>test: %p\n", *group->cmds->cmd_args[i]);
// 		ft_format_redirs(group, i);
// 		// ft_pickup_redirs(group, i);
// 		ft_extract_redirs(group, i);
// 		i++;
// 	}
// 	return (0);
// }
