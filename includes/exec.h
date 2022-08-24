/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:18:43 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 14:01:58 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "exec.h"
///////here doc
char	*read_stdin(char *limiter, char *file);
///in n out files
void	check_infile(t_group *group, t_msh *msh, int j);
void	check_outfile(t_group *group, int j);
//////// errors
void	check_dup2(int n);
void	check_dup(int n);
void	check_pipe(int n);
//////path
char	**get_paths(char **env);
char	*get_correct_path(char **cmd, t_msh *msh);
////////////fds
int		set_std_i_o(t_cmds *cmd, t_msh *msh);
void	close_fds_parent(t_group *group, t_msh *msh, int cmd_num);
void	close_fds_child(t_group *group, t_msh *msh, int cmd_num);
/////////utils
void	check_what_redirs(t_group *group, t_msh *msh, int j);
void	init_data4group(t_msh *msh);
void	builtin_or_exec(t_group *group, t_msh *msh, int cmd_num, int j);
void	if_redirs_or_null(t_group *group, t_msh *msh, int j);
void	ft_parse_group(t_msh *msh, int group_i);
////////free
void    ft_free_exec(t_msh *msh);
void	free_env_list(t_env **env_list);
///////////exec
void    ft_execve(char **cmd, t_msh *msh);
void	exec_group(t_group *group, t_msh *msh);
void	ft_prep_exec(t_msh *msh);
void	ft_exec(void);
int		redirect_parent(char **cmd, int cmd_num, t_msh *msh);
int		edirect_child(char **cmd, t_msh *msh);
int		exec_cmds(char **cmd, t_group *group, t_msh *msh, int cmd_num);
#endif