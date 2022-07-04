/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:52:33 by vangirov          #+#    #+#             */
/*   Updated: 2022/06/24 17:21:28 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/* AND and OR should not be indexed with 0*/

// FIELDS
#define LX_FIELD		0	// ''
#define LX_EXT_FIELD	1	// ""
#define LX_VAR			2	// $
// SINGLES
#define LX_WC			3	// *
// HALVES
#define LX_PIPE			4	// |
#define LX_REDIR_OUT	5	// >
#define LX_REDIR_IN		6	// <
// DOUBLES
#define LX_AND			7	// &&
#define LX_OR			8	// ||
#define LX_REDIR_APPEND	9	// >>
#define LX_REDIR_INSRC	10	// <<

#define LX_NUM			11
#define LX_WORD			LX_NUM
#define LX_SEP			99

// typedef enum Lx
// {
// 	FIELD,
// 	EXT_FIELD,
// 	VAR,				// $
// // SINGLES
// 	LX_WC,				// *
// // HALVES
// 	PIPE,				// |
// 	REDIR_OUT,		// >
// 	REDIR_IN,			// <
// // DOUBLES
// 	AND,				// &&
// 	OR,				// ||
// 	REDIR_APPEND,		// >>
// 	REDIR_INSRC,		// <<

// 	WORD,
// 	SEP,
// 	LXNUM,
// }	Lx;


typedef struct s_lexem
{
	int		type;
	char	*text;
}	t_lexem;

// lexer.c
void	ft_init_delims(t_msh *msh);
void	ft_lexer(char *line, t_msh *msh);
char	*ft_skip_spaces(char *ptr, t_msh *msh);
char	*ft_findsym(char *ptr, t_msh *msh);
char	*ft_getfield(int lx_type, char *ptr, t_msh *msh);
char	*ft_gettext(char *ptr, int len);
int		ft_have_inters(char *s1, char *s2);

// lists.c
t_list	*ft_lst_penult(t_list *lst);
t_lexem	*ft_newlexem(int lx_type, char *text);
void	ft_addlexem(t_list **lexems, t_lexem *lexem);
void	ft_dellastsep(t_list **lexems);
char	*ft_ectracttext(t_list *link);
int		ft_ectracttype(t_list *link);

#endif