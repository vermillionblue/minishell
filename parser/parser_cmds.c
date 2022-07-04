/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:33:00 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/04 15:30:15 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_error(char *error_text, int error_num)
{
	ft_fdprintf(2, "minishell: %s\n (%d)\n", error_text, -error_num);
	return (error_num);
}

/* if the first token is AND or OR print error */
int	ft_count_cmds(t_list **lexems)
{
	int	counter;
	int type;

	t_list *link;
	if (ft_lstsize(*lexems) == 1)
		return (0);
	counter = 1;
	link = *lexems;
	type = ft_ectracttype(link);
	if (type == LX_PIPE)
		return(ft_error("syntax error: || or && as the first token", -401));
	type = ft_ectracttype(ft_lstlast(link));
	if (type == LX_PIPE)
		return(ft_error("syntax error: || or && as the last token", -499));
	while (link)
	{
		type = ft_ectracttype(link);
		if (type == LX_PIPE)
			counter++;
		link = link->next;
	}
	return (counter);
}

int	ft_makegroups(t_msh *msh)
{
	// int		gr_num;
	int		i;
	t_list	*link;
	int		type;
	char	*text;

	if (msh->group_num <= 0)
		return(ft_error("could not parse", -300));
	
	msh->groups = malloc(sizeof(t_group *) * msh->group_num);
	i = 0;
	link = *msh->lexems;
	while (i < msh->group_num)
	{
		msh->groups[i] = malloc(sizeof(t_group));
		msh->groups[i]->lexems = malloc(sizeof(t_list *));
		*msh->groups[i]->lexems = NULL;
		if (i == 0)
			msh->groups[i]->type = 0;
		else
			msh->groups[i]->type = ft_ectracttype(link);
		while (link)
		{
			type = ft_ectracttype(link);
			if ((type == LX_AND || type == LX_OR) && *msh->groups[i]->lexems)
				break ;
			text = ft_ectracttext(link);
			ft_addlexem(msh->groups[i]->lexems, ft_newlexem(type, text));
			link = link->next;
		}
		ft_dellastsep(msh->groups[i]->lexems);
		i++;
	}
	return (0);
}


void	ft_parser(t_msh *msh);
        //   ls -la | echo gekee && make re       