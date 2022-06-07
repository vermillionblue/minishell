/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:22:38 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/25 21:03:11 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_double(char **string)
{
	int	i;

	i = 0;
	while (string[i] != NULL)
	{
		free(string[i]);
		i++;
	}
	free(string[i]);
	free(string);
}

void	execute_cmds(char **env, char **paths, char *argv)
{
	char	*a_path;
	char	**cmd;
	int		id;
	int		fd[2];

	check_pipe(pipe(fd));
	check_fork(id = fork());
	if (id == 0)
	{
		cmd = ft_split(argv, ' ');
		a_path = get_correct_path(paths, cmd);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(a_path, cmd, env) == -1)
			exit (EXIT_FAILURE);
	}
	waitpid(id, NULL, WNOHANG);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
}

int	exec_last(int argc, char **argv, char **env, char **paths)
{
	int		id;
	char	**cmd;
	char	*a_path;
	int		status;

	check_fork(id = fork());
	if (id == 0)
	{
		cmd = ft_split(argv[argc - 2], ' ');
		a_path = get_correct_path(paths, cmd);
		execve(a_path, cmd, env);
		free(a_path);
		free_double(cmd);
		exit (EXIT_FAILURE);
	}
	waitpid(id, &status, WNOHANG);
	return (status);
}

int	set_fds(int fd[2], char **argv, int argc, char *file)
{
	int	i;

	if (!ft_strncmp("here_doc", argv[1], 8))
	{	
		fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		file = read_stdin(argv[2], file);
		fd[0] = open(file, O_RDONLY);
		i = 2;
	}
	else
	{
		fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		fd[0] = open(argv[1], O_RDONLY);
		i = 1;
	}
	dup2(fd[0], STDIN_FILENO);
	return (i);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	char	**paths;
	int		status;
	int		i;
	char	*tempfile;

	tempfile = ".here_doc";
	if (argc < 5)
		return (1);
	i = set_fds(fd, argv, argc, tempfile);
	paths = get_paths(env);
	while (++i < argc - 2)
		execute_cmds(env, paths, argv[i]);
	dup2(fd[1], STDOUT_FILENO);
	status = exec_last(argc, argv, env, paths);
	free_double(paths);
	clean_here_doc(argv[1], tempfile);
	return (status);
}
