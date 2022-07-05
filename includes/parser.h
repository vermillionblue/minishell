/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:34:14 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/05 10:17:07 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

int		ft_makegroups(t_msh *msh);
int		ft_count_groups(t_list **lexems);
int		ft_create_cmds(t_msh *msh);
int		ft_make_cmd_args(t_group *group);
int		ft_make_newargvs(t_group *group);
int		ft_unite_texts(t_group *group);
int		ft_count_args(t_list **cmd_args);
char	*ft_strjoinfree(char *tofree1, char *tofree2);
int	ft_make_redirs(t_group *group);

// redirs
t_list	*ft_lst_shift_head_n(t_list **head, int n);
t_list	*ft_lst_find_preceding(t_list **head, t_list *target);
t_list	*ft_lst_detach_from(t_list **headfrom, t_list *target);
t_list	*ft_lstpush_behind_link(t_list **hf, t_list *t, t_list **ht, t_list *d);
t_list	*ft_lstpush_before_link(t_list **hf, t_list *t, t_list **ht, t_list *d);

void	ft_loop_cmds(t_group *group, void (*opearation)(t_group *, int i));
void	ft_init_redirs(t_group *group, int cmd_i);
void	ft_extract_redirs(t_group *group, int cmd_i);
void	ft_format_redirs(t_group *group, int cmd_i);
////printing
void	ft_printlexems(t_list **lexems);
void	ft_print_arg_redir(t_group *group);
void	ft_print_newargvs(t_group *group);
void ft_print_groups(t_msh *msh);

#endif
