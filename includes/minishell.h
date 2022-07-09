/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:07 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/09 15:53:06 by danisanc         ###   ########.fr       */
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
////pipes
# define READ_END 0
# define WRITE_END 1
////////////////////
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> /// For Open 
# include <signal.h>  /// For Signals
# include <sys/wait.h>  /// For Wait
# include <readline/readline.h>  /// For Readline
# include <readline/history.h>  /// For History
# include <sys/stat.h>  /// For lstats
# include <dirent.h>
# include <errno.h>
# include <limits.h> //include PATH_MAX
/* Our Libraries */
# include "../libft/libft.h"
# include "../vlad_printf/ft_printf.h"

typedef struct s_env
{
	char			*bash_variable;
	char			*bash_v_content;
	int				sort;
	struct s_env	*next;
} t_env;

typedef struct s_cmds
{
	char	**env;			// no yet, wait for Dani
	int		cmd_num;
	int		pipe_num;
	char	*infile_name;	// no yet
	char	*outfile_name;	// no yet
	int		infile_fd;		// no yet
	int		outfile_fd;	
	int		append_outfile; //boolean
	int		here_doc;	// boolean
	char	**paths;		// no yet
	int		**pipes;	
	int		lx_pt;	// no yet, wait for Dani (depends on env)
	char	**cmd_names;
	t_list	***cmd_args;
	char	***newargvs;
	t_list	***redirs;
}	t_cmds;

typedef struct s_group
{
	int		index;
	int		type;
	t_list	**lexems;
	t_cmds	*cmds;
}	t_group;

typedef struct s_msh
{
	// t_env	*env;oh
	char	**builtins;
	char	**delims;
	t_list	**lexems;
	int		group_num;
	t_group	**groups;
	char	**paths;
	int		last_exit_stat;
	char	**env;
	t_env	**env_list;
	int		*temp_i_o;
}	t_msh;

/* Linked Lists Utils */
t_list	*create_element(char **value);
void	print_list(t_list **stack);
void	free_list(t_list **list);
void	delete_list(t_list **list);
char    *expand_wildcard(char *raw_cmd);
/////signals
void	ft_signal_child(void);
void    ft_signal_parent(void);

# include "lexer.h"
# include "parser.h"
# include "exec.h"

#endif