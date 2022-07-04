/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:13:13 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/04 15:29:42 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	ft_init_delims(t_msh *msh)
{
	char	**delims;
	// int		i;

	delims = malloc(sizeof(char *) * (LX_NUM + 1));
	// i = 0;
	// while (i < 0)
	// {
	delims[LX_FIELD] = "''";
	delims[LX_EXT_FIELD] = "\"\"";
	delims[LX_VAR] = "$$ *"; //should also finish with <>&&
	delims[LX_WC] = "*";
	
	delims[LX_PIPE] = "|";
	delims[LX_REDIR_OUT] = ">";
	delims[LX_REDIR_IN] = "<";

	delims[LX_AND] = "&&";
	delims[LX_OR] = "||";
	delims[LX_REDIR_APPEND] = ">>";
	delims[LX_REDIR_INSRC] = "<<";

	delims[LX_NUM] = "  $*|'\"><&";
	// }
	msh->delims = delims;
}

char	*ft_gettext(char *ptr, int len)
{
	char	*text;
	int		i;

	text = malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < len)
	{
		text[i] = ptr[i];
		i++;
	}
	text[i] = '\0';
	return (text);
}

char	*ft_skip_spaces(char *ptr, t_msh *msh)
{
	int	sep;

	sep = 0;
	while (*ptr && *ptr == ' ')
	{
		ptr++;
		sep++;
	}
	if (sep && ft_lstsize(*msh->lexems))
		ft_addlexem(msh->lexems, ft_newlexem(LX_SEP, ""));
	return (ptr);
}

char	*ft_getfield(int lx_type, char *ptr, t_msh *msh)
{
	int		len;
	char	*start;
	char	*closings;

	closings = msh->delims[lx_type] + 1;
	len = 0;
	start = ptr;
	while (*ptr && !ft_strchr(closings, *ptr))
	{
		len++;
		ptr++;
	}
	ft_addlexem(msh->lexems, ft_newlexem(lx_type, ft_gettext(start, len)));
	if (*ptr && lx_type <= LX_EXT_FIELD)
		ptr++;
	return (ptr);
}

char	*ft_chr2str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = 0;
	return (str);
}

char	*ft_intersect(char *s1, char *s2)
{
	char	*intersection;
	
	intersection = ft_strdup("");
	while (*s1)
	{
		printf(">>> %c\n", *s1);
		if (!ft_strchr(s1 + 1, *s1) && ft_strchr(s2, *s1))
		{
			intersection = ft_strjoinfree(intersection, ft_chr2str(*s1));
		}
		s1++;
	}
	if (ft_strlen(intersection))
		return (intersection);
	else
	{
		free(intersection);
		return (NULL);
	}
}

int	ft_have_inters(char *s1, char *s2)
{
	char	*intersection;
	int		len;
	
	len = 0;
	intersection = ft_intersect(s1, s2);
	if (intersection)
	{
		len = ft_strlen(intersection);
		if (len)
			free(intersection);
	}
	return (len);
}

char	*ft_findsym(char *ptr, t_msh *msh)
{
	int		i;
	// char	*closings;

	i = 0;
	while (*ptr && i < LX_NUM)
	{
		if (*ptr == msh->delims[i][0])
		{
			// closings = msh->delims[i] + 1;
			if (i <= 2) // && ft_have_inters(ptr + 1, closings)) // FIELD
			{
				// printf("closings: %s\n", closings);
				return (ft_getfield(i, ++ptr, msh));
			}
			else if (i == 3 || (i > 3 && i <= 6 && *(ptr + 1) && *(ptr + 1) != *ptr)) // SINGLE
			{
				printf("Test SINGLE (%c): %c ~ %c\n", *(ptr - 1), *ptr, *(ptr + 1));
				ft_addlexem(msh->lexems, ft_newlexem(i, ""));
				return (ptr + 1);
			}
			else if (i == 7 && ((*(ptr + 1) && *(ptr + 1) != *ptr) || !*(ptr + 1)))
			{
				ft_addlexem(msh->lexems, ft_newlexem(LX_WORD, ft_chr2str(*ptr)));
				return (ptr + 1);
			}
			else if (i >= 7 && i <= 10 && *(ptr + 1) == *ptr) // DOUBLE
			{
				printf("Test DOUBLE (%c): %c ~ %c\n", *(ptr - 1), *ptr, *(ptr + 1));
				ft_addlexem(msh->lexems, ft_newlexem(i, ""));
				return (ptr + 2);
			}
			// else
			// {
			// 	printf("[%d] Test LAST (%c): %c ~ %c$\n", i, *(ptr - 1), *ptr, *(ptr + 1));
			// 	ft_addlexem(msh->lexems, ft_newlexem(LX_WORD, ft_chr2str(*ptr)));
			// 	return (ptr + 1);
			// }
		}
		i++;
	}
	return (ptr);
}

void	ft_lexer(char *line, t_msh *msh)
{
	char	*ptr;
	char	*tmp;

	msh->lexems = malloc(sizeof(t_list *));
	*msh->lexems = NULL;
	ptr = line;
	while (*ptr)
	{
		ptr = ft_skip_spaces(ptr, msh);
		tmp = ft_findsym(ptr, msh);
		if (*ptr && ptr == tmp)
		{
			ptr = ft_getfield(LX_WORD, ptr, msh);
		}
		else
			ptr = tmp;
	}
	ft_dellastsep(msh->lexems);
}
