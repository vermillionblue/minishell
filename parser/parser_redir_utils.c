/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:39:08 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/06 15:15:03 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_lst_shift_head_n(t_list **head, int n)
{
	t_list	*link;

	if (!head)
		return (NULL);
	link = *head;
	while (n-- && link)
	{
		*head = link->next;
		link = link->next;
	}
	return (*head);
}

/*	Returns NULL if head does not exist or points to NULL (i.e.
	there are no links in the list) or there is no link
	between the head and he target link */
t_list	*ft_lst_find_preceding(t_list **head, t_list *target)
{
	t_list	*link;

	if (!head)
		return (NULL);
	if (*head == target)
		return (NULL);
	link = *head;
	while (link)
	{
		// printf("finding prec: %s\n", ft_ectracttext(link));
		if (link->next == target)
			return (link);
		link = link-> next;
	}
	return (NULL);
}

t_list	*ft_lst_detach_from(t_list **headfrom, t_list *target)
{
	t_list	*preceding;

	printf("TEST >>>\n");
	if (!headfrom)
		exit(1);
	if (*headfrom == target)
		*headfrom = ft_lst_shift_head_n(headfrom, 1);
	else
	{
		preceding = ft_lst_find_preceding(headfrom, target);
		// if (preceding)
		// 	printf("prec: %s, %d\n", ft_ectracttext(preceding), ft_ectracttype(preceding->next));
		if (preceding)
			preceding->next = target->next;
		// if (preceding->next)
		// 	printf("next: %s, %d\n", ft_ectracttext(preceding->next), ft_ectracttype(preceding->next));
	}
	target->next = NULL;
	return (target);
}

void	ft_free_lexem(t_list *link)
{
	// if (ft_ectracttype(link) <= LX_VAR)
	free(ft_ectracttext(link));
	free(link->content);
	free(link);
}

char	*ft_strjoinfree(char *tofree1, char *tofree2)
{
	char	*newline;

	newline = ft_strjoin(tofree1, tofree2);
	free(tofree1);
	free(tofree2);
	return (newline);
}

// char	*ft_concat(char *line, char *nonl_buff)
// {
// 	char	*newline;

// 	newline = ft_strjoin(line, nonl_buff);
// 	free(line);
// 	return (newline);
// }

// /* hf (head_from), ht (head_to), t (target), d(destination) */
// t_list	*ft_lstpush_behind_link(t_list **hf, t_list *t, t_list **ht, t_list *d)
// {
// 	t_list	*target;

// 	if (!ht)
// 		return (NULL);
// 	target = ft_lst_detach_from(hf, t);
// 	if (!target)
// 		return (NULL);
// 	if (!d)
// 	{
// 		ft_lstadd_back(ht, target);
// 		return target;
// 	}
// 	target->next = d->next;
// 	d->next = target;
// 	return (target);
// }

// t_list	*ft_lstpush_before_link(t_list **hf, t_list *t, t_list **ht, t_list *d)
// {
// 	t_list	*target;
// 	t_list	*preceding;

// 	if (!ht)
// 		return (NULL);
// 	target = ft_lst_detach_from(hf, t);
// 	if (!target)
// 		return (NULL);
// 	preceding = ft_lst_find_preceding(ht, d);
// 	if (*ht && !preceding)
// 	{
// 		*ht = target;
// 	}
// 	else
// 	{
// 		preceding->next = target;
// 	}
// 	target->next = d;
// 	return (target);
// }

