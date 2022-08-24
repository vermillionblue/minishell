/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:52:33 by vangirov          #+#    #+#             */
/*   Updated: 2022/08/24 15:37:16 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/* AND and OR should not be indexed with 0*/
// FIELDS
	// ()
# define LX_PAR			0
# define LX_FIELD		1	// ''
# define LX_EXT_FIELD	2	// ""
# define LX_VAR			3	// $
// SINGLES
// #define LX_WC			3	// *
// HALVES
# define LX_PIPE			4	// |
# define LX_REDIR_OUT	5	// >
# define LX_REDIR_IN		6	// <
// DOUBLES
# define LX_AND			7	// &&
# define LX_OR			8	// ||
# define LX_REDIR_APPEND	9	// >>
# define LX_REDIR_INSRC	10	// <<
# define LX_NUM			11
# define LX_WORD			LX_NUM
# define LX_SEP			99

typedef struct s_lexem
{
	int		type;
	char	*text;
}	t_lexem;

typedef struct s_msh t_msh;
typedef struct s_group t_group;
typedef struct s_env t_env;
typedef struct s_cmds t_cmds;
// lexer.c
void	ft_init_delims(t_msh *msh);
void	ft_lexer(char *line, t_msh *msh);
char	*ft_skip_spaces(char *ptr, t_msh *msh);
char	*ft_findsym(char *ptr, t_msh *msh);
char	*ft_getfield(int lx_type, char *ptr, t_msh *msh);
char	*ft_gettext(char *ptr, int len);
int		ft_have_inters(char *s1, char *s2);
char	*ft_chr2str(char c);
# include "minishell.h"
// lists.c
t_list	*ft_lst_penult(t_list *lst);
t_lexem	*ft_newlexem(int lx_type, char *text);
void	ft_addlexem(t_list **lexems, t_lexem *lexem);
void	ft_dellastsep(t_list **lexems);
char	*ft_ectracttext(t_list *link);
int		ft_ectracttype(t_list *link);

#endif
