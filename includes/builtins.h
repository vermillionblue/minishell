/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:14:36 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/23 19:25:41 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
//export
typedef struct s_env
{
	char			*bash_variable;
	char			*bash_v_content;
	int				sort;
	struct s_env	*next;
} t_env;


int		do_export(t_env **env_list, char *args);
void	print_sorted_export(t_env **env_list);
t_env	*find_env_node(t_env **env_list, char *name);
void	set_sort_var(t_env **env_list);
void	get_name_arg(t_env *new_env, char *args, t_env **env_list);
unsigned int	env_list_size(t_env **env_list);

int		do_cwd(void);
int		do_unset(t_env **env_list, char *name);
void	do_exit(void);
int		do_cd(char *path);
/*				ENV List			*/
t_env	*create_env_list(char	**envp);
t_env	*create_env_element(char **value);
void	append_env_element(t_env **lst, t_env *new);
void	print_env_list(t_env **env_list);
char    **list_to_arr(t_env **env_list);

void	ft_redirect(char *line, t_env *env_list);
#endif