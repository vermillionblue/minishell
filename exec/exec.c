/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:24:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/29 13:20:46 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	print_arr(char **env)
{
	int i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (1);
}

int	ft_redirect(char *line, t_env *env_list, char **env)
{
	char	**args;
	int		res;
	
	res = 0;
    args = ft_split(line, ' ');
	if (!ft_strncmp(args[0], "cd", 3))
		res = do_cd(check_if_no_args(args));
	else if (!ft_strncmp(args[0], "pwd", 4))
		res = do_cwd();
	else if (!ft_strncmp(args[0], "env", 4))
		print_env_list(&env_list);
	else if (!ft_strncmp(args[0], "export", 7))
		res = do_export(&env_list, check_if_no_args(args));
	else if (!ft_strncmp(args[0], "unset", 6))
		res = do_unset(&env_list, check_if_no_args(args));
	else if (!ft_strncmp(args[0], "exit", 5))
		do_exit();
	else if (!ft_strncmp(args[0], "echo", 5) && !ft_strncmp(args[1], "-n", 3))
		res = do_echo(args);
	else if (!ft_strncmp(args[0], "exec", 5))
		start_exec(env);
	else
		ft_exec();
	return (res);
}

char	*get_correct_path(char **paths, char **cmd)
{
	int		i;
	char	*a_path;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		a_path = ft_strjoin(temp, cmd[0]);
		if (access(a_path, F_OK) == 0)
			return (a_path);
		i++;
	}
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(" : command not found\n ", 2);
	exit (EXIT_FAILURE);
}

char	**get_paths(char **env)
{
	int		i;
	char	**temp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{	
			ft_memmove(env[i], env[i] + 5, ft_strlen(env[i]));
			temp = ft_split(env[i], ':');
			return (temp);
		}
		i++;
	}
	exit (EXIT_FAILURE);
}

t_list	*create_cmds()
{
    t_list *head;
    t_list *sec;
    t_list  *third;
    t_list  *tail;

	third = NULL;
	sec = NULL;
	head = NULL;
	tail = NULL;
	
	third = malloc(sizeof(t_list));
	sec = malloc(sizeof(t_list));
	head = malloc(sizeof(t_list));
	tail = malloc(sizeof(t_list));
	
    head->content = expand_wildcard("ls *sterisk*");
    head->next = sec;
    
    sec->content = "cat";
    sec->next = third;

    third->content = "cat";
    third->next = tail;

    tail->content = "cat -e";
    tail->next = NULL;
    return (head);
}

void	exec_cmds(t_list *cmds, char **env, char **paths)
{
	int		fd[2];
    int		id;
	char	**cmd;
	char	*a_path;

    pipe(fd);
	id = fork();
	if (id == 0)
	{
		cmd = ft_split(cmds->content, ' ');
		a_path = get_correct_path(paths, cmd);
		dup2(fd[1], STDOUT_FILENO);
		//close(fd[1]);
		close(fd[0]);
		if (execve(a_path, cmd, env) == -1)
			exit (EXIT_FAILURE);
	}
	waitpid(id, NULL, WNOHANG);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	//close(fd[0]);
}

int	exec_last(t_list *cmds, char **env, char **paths)
{
    int		id;
	char	**cmd;
	char	*a_path;
	int		status;

	id = fork();
	if (id == 0)
	{
		cmd = ft_split(cmds->content, ' ');
		a_path = get_correct_path(paths, cmd);
		if (execve(a_path, cmd, env) == -1)
		{
			perror(" error with execv\n");
			exit (EXIT_FAILURE);
		}
	}
	waitpid(id, &status, 0);
	return (status);
}

int	start_exec(char **env)
{
    t_list  *cmds;
    char	*files[3];
    char	*tempfile;
	char	**paths;
	int		res;
	int		fd[2];

	tempfile = ".here_doc";
	//files[0] = "outtrunc.txt";
	//files[1] = "outapp.txt";
	files[2] = "infile.txt";
    //files = ["outtrunc.txt", "outapp.txt", "infile.txt"];
	paths = get_paths(env);
    cmds = create_cmds();
    // if (files[1] != "0")
    //     fd[1] = open(files[0], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    //fd[1] = open(files[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	//printf("%d\n", fd[1]);
    fd[0] = open(files[2], O_RDONLY);
    // dup2(fd[0], STDIN_FILENO);
    while (cmds->next)
    {
        exec_cmds(cmds, env, paths);
        cmds = cmds->next;
    }
	//dup2(1, STDOUT_FILENO);
	//printf("%s executed\n", cmds->content);
	res = exec_last(cmds, env, paths);
	return (res);
	//exit(EXIT_SUCCESS);
}

void	ft_exec()
{
	printf("miau");
}
