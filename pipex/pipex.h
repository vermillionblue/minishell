/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:13:45 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/25 21:08:37 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

char	*ft_sttrjoin(char const *s1, char const *s2);
//errors
void	check_fork(int id);
void	check_pipe(int fd);
//parse
char	**get_paths(char **env);
char	*get_correct_path(char **paths, char **cmd);
//bonus
char	*read_stdin(char *limiter, char *file);
void	clean_here_doc(char *start, char *file);
#endif
