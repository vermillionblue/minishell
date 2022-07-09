/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:48:18 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/09 12:31:35 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exchange_link_for_list(t_list **head, t_list *target, t_list *newfirst)
{
	t_list	*preceding;

	if (!head)
		exit(1);
	if (*head == target)
		*head = newfirst;
	else
	{
		preceding = ft_lst_find_preceding(head, target);
		if (preceding)
			preceding->next = newfirst;
	}
	ft_lstlast(newfirst)->next = target->next;
	ft_free_lexem(target);
}

void	ft_print_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("[%2d] %s\n", i, arr[i]);
		i++;
	}
}

t_list	*ft_expanded2list(char *expanded)
{
	char	**arr;
	int		i;
	t_list	*newfirst;
	
	arr = ft_split(expanded, ' ');
	free(expanded);
	i = 0;
	while(arr[i])
	{
		if (i == 0)
		{
			newfirst = malloc(sizeof(t_list));
			newfirst->content = ft_newlexem(LX_WORD, arr[i]);
			newfirst->next = NULL;
		}
		else
		{
			ft_addlexem(&newfirst, ft_newlexem(LX_SEP, ft_strdup("")));
			ft_addlexem(&newfirst, ft_newlexem(LX_WORD, arr[i]));
		}
		i++;
	}
	free(arr);
	return (newfirst);
}

int	ft_expand_wcs(t_group *group)
{
	int		cmd_i;
	t_list	*link;
	t_list	*next;
	t_list	*newfirst;
	char	*expanded;

	cmd_i = 0;
	while (cmd_i < group->cmds->cmd_num)
	{
		link = *group->cmds->cmd_args[cmd_i];
		while (link)
		{
			next = link->next;
			if (ft_ectracttype(link) == LX_WORD && \
				ft_strchr(ft_ectracttext(link), '*'))
			{
				printf("To extend: \"%s\"\n", ft_ectracttext(link));
				expanded = expand_wildcard(ft_ectracttext(link));
				printf("Expanded: %s\n", expanded);
				newfirst = ft_expanded2list(expanded);
				ft_printlexems(&newfirst);
				ft_exchange_link_for_list(group->cmds->cmd_args[cmd_i], \
					link, newfirst);
				ft_printlexems(group->cmds->cmd_args[cmd_i]);
			}
			link = next;
		}
		cmd_i++;
	}
	return (0);
}