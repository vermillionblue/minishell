/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:14:36 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/09 12:12:45 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"
/////////export
int		do_export(t_env **env_list, char *args);
void	print_sorted_export(t_env **env_list);
t_env	*find_env_node(t_env **env_list, char *name);
void	set_sort_var(t_env **env_list);
int		get_name_arg(t_env *new_env, char *args, t_env **env_list);
unsigned int	env_list_size(t_env **env_list);
char	*check_if_no_args(char **args);
int		do_echo(char **args);
int		do_cwd(void);
int		do_unset(t_env **env_list, char *name);
void	do_exit(void);
int		do_cd(char *path);
////////////
t_env	*create_env_list(char	**envp);
t_env	*create_env_element(char **value);
void	append_env_element(t_env **lst, t_env *new);
int		print_env_list(t_env **env_list);
char    **list_to_arr(t_env **env_list);
//exec
int		ft_redirect(t_msh *msh, t_env *env_list, char **env);

#endif