/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:18:43 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/12 14:14:20 by danisanc         ###   ########.fr       */
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
void	check_dup(int n);
void	check_pipe(int n);
//////path
char	**get_paths(char **env, t_msh *msh);
char	*get_correct_path(char **cmd, t_msh *msh);
////////////fds
void	set_std_i_o(t_cmds *cmd, t_msh *msh);
void	close_fds_parent(t_group *group, t_msh *msh);
void	close_fds_child(t_group *group, t_msh *msh);
///////////exec
void	exec_group(t_group *group, t_msh *msh);
void	ft_prep_exec(t_msh *msh, t_env **env_list);
void	ft_exec(void);

#endif