/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:24:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/08 15:27:08 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//1 outputfile trunc
//2 output file append
//3 infile
// t_list  *create_files()
// {
//     t_list *files;

//     files = 
// }

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

	head = malloc(sizeof(t_list));
    head->line = ft_strdup("ls -l");
    head->next = sec;
    
	sec = malloc(sizeof(t_list));
    sec->line = ft_strdup("ls -l");
    sec->next = third;
    
	third = malloc(sizeof(t_list));
    third->line = ft_strdup("ls -l");
    third->next = tail;

	tail = malloc(sizeof(t_list));
    tail->line = ft_strdup("ls -l");
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
		cmd = ft_split(cmds->line, ' ');
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

void    start_exec(char **env)
{
    t_list  *cmds;
    char	*files[3];
    char	*tempfile;
	char	**paths;
	int		fd[2];

	tempfile = ".here_doc";
	files[0] = "outtrunc.txt";
	files[1] = "0";
	files[2] = "infile.txt";
    //files = ["outtrunc.txt", "outapp.txt", "infile.txt"];
	paths = get_paths(env);
    cmds = create_cmds();
    // if (files[1] != "0")
    //     fd[1] = open(files[0], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    fd[1] = open(files[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	printf("%d\n", fd[1]);
    fd[0] = open(files[2], O_RDONLY);
	printf("%d\n", fd[0]);
    dup2(fd[0], STDIN_FILENO);
	printf("%d\n", fd[0]);
    while (cmds->next)
    {
        exec_cmds(cmds, env, paths);
        cmds = cmds->next;
    }
		
}
