/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:10:15 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/06 14:50:29 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_expand_all_groups_vars(t_msh *msh)
{
	int	i;

	i = 0;
	while (i < msh->group_num)
	{
		ft_expand_gr_vars(msh, i);
	}
}

void	ft_expand_gr_vars(t_msh *msh, int group_i)
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

int	ft_get_var_len(char *ptr, t_msh *msh)
{
	int		len;
	// char	*start;
	char	*closings;

	closings = msh->delims[LX_VAR] + 1;
	len = 0;
	// start = ptr;
	while (*ptr && !ft_strchr(closings, *ptr))
	{
		len++;
		ptr++;
	}
	return (len);
}

// 	name = ft_gettext(start, len);
// 	var = find_env_node(&(msh->env_list), name);
// 	if (var)
// 	{
// 		value = ft_strdup(var->bash_v_content);
// 		free(name);
// 	}
// 	else
// 	{
// 		ft_lst_detach_from(msh->groups[group_i]->lexems, link);
// 		// free((*(t_lexem *)link->content).text);
// 		// free(link);
// 	}
// 	if (*ptr && lx_type <= LX_EXT_FIELD)
// 		ptr++;
// 	return (ptr);
// }

char	*ft_expand_text(t_msh *msh, char *text)
{
	char	*ptr;
	char	*ret;
	char	*name;
	t_env	*var;
	// char	*value;
	int		len;

	ptr = text;
	ret = malloc(sizeof(char));
	ret[0] = '\0';
	while (*ptr)
	{
		if (*ptr != '$')
		{
			ret = ft_strjoinfree(ret, ft_chr2str(*ptr));
			ptr++;
		}
		else
		{
			len = ft_get_var_len(++ptr, msh);
			name = ft_gettext(ptr, len);
			printf("LEN: %d\n", len);
			var = find_env_node(&(msh->env_list), name);
			free(name);
			if (var)
			{
				ret = ft_strjoinfree(ret, ft_strdup(var->bash_v_content));
			}
			ptr += len;
		}
	}
	return (ret);
}

void	ft_expand_gr_fields(t_msh *msh, int group_i)
{
	t_list	*link;
	t_list	*next;
	char	*text;
	char	*expanded;

	link = *msh->groups[group_i]->lexems;
	while(link)
	{
		next = link->next;
		if (ft_ectracttype(link) == LX_EXT_FIELD)
		{
			text = (*(t_lexem *)link->content).text;
			expanded = ft_expand_text(msh, text);
			free(text);
			(*(t_lexem *)link->content).text = expanded;
		}
		link = next;
	}
}
