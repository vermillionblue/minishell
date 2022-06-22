/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:07 by vsimeono          #+#    #+#             */
/*   Updated: 2022/06/22 11:42:30 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

 ///colors
# define GREEN "\033[0;32m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

//# define GENERATE_STRING(STRING) #STRING,
# define str(x) #x
# define xstr(x) str(x)
# define FOREACH_CMD(CMD) \
		//CMD(cd) \
		CMD(export) \
		CMD(env) \
		CMD(exit) \
		CMD(unset) \
		CMD(pwd) \
		CMD(echo) \

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> /// For Open 
# include <signal.h>  /// For Signals
# include <sys/wait.h>  /// For Wait
# include <readline/readline.h>  /// For Readline
# include <readline/history.h>  /// For History
# include <sys/stat.h>  /// For lstats
// # include <sys/types.h> /// TODO V - Can't remember what I did here
//# include <linux/limits.h> //include PATH_MAX
# include <limits.h> //include PATH_MAX
/* Libft Library */
# include "libft/libft.h"




typedef struct s_env
{
	char			*bash_variable;
	char			*bash_v_content;
	int				sort;
	struct s_env	*next;
} t_env;

/* 1 Module Lexar */
// void	create_lexar(t_list *lexar_list, char **array);   
void	create_lexar(t_list *lexar_list, char *line);   

int		size_of_array(char **array);

	/* Linked Lists Utils */
t_list	*create_element(char **value);
void	print_list(t_list **stack);
void	free_list(t_list **list);
void	delete_list(t_list **list);

/*				ENV List			*/
// t_env		create_env_list(char	**envp);
t_env	*create_env_list(char	**envp);
t_env	*create_env_element(char **value);
void	ft_lstadd_back_env_element(t_env **lst, t_env *new);
void	print_env_list(t_env **env_list);

///built-ins

//export
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

//exec
void    start_exec(char **env);

#endif