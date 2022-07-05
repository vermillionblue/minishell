/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:24:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/05 20:22:13 by danisanc         ###   ########.fr       */
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

int	ft_redirect(t_msh *msh, t_env *env_list, char **env)
{
	char	**args;
	int		res;
	
	res = 0;
	args = msh->groups[0]->cmds->newargvs[0];
	printf("===========result=================================\n");
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
	else
		start_exec(env, msh);
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
	ft_putstr_fd(": command not found\n ", 2);
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
    sec->next = NULL;

    third->content = "cat";
    third->next = tail;

    tail->content = "cat -e";
    tail->next = NULL;
    return (head);
}

void	if_dup_fail(int n)
{
	if (n < 0)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
}

int	exec_cmds(char **cmd, char **env, char **paths, t_msh *msh)
{
	int		fd[2];
    int		id;
	char	*a_path;

    pipe(fd);
	id = fork();
	if (id == 0)
	{
		//cmd = ft_split(cmds->content, ' ');
		a_path = get_correct_path(paths, cmd);
		close(fd[READ_END]);
		if_dup_fail(dup2(fd[WRITE_END], STDOUT_FILENO));
		close(fd[WRITE_END]);
		if (execve(a_path, cmd, env) == -1)
			exit (EXIT_FAILURE);
	}
	waitpid(-1, NULL, 0);
	close(fd[WRITE_END]);
	if_dup_fail(dup2(fd[READ_END], STDIN_FILENO));
	close(fd[READ_END]);
	
}

int	exec_last(char **cmd, char **env, char **paths)
{
    int		id;
	char	*a_path;
	int		status;

	id = fork();
	if (id == 0)
	{
		//cmd = ft_split(cmds->content, ' ');
		a_path = get_correct_path(paths, cmd);
		//rl_replace_line("", 0);
		if (execve(a_path, cmd, env) == -1)
		{
			perror("error with execv\n");
			exit (EXIT_FAILURE);
		}
	}
	waitpid(id, &status, 0);
	return (status);
}

int	start_exec(char **env, t_msh *msh)
{
    char  **cmds;
	char	**paths;
	int		res;
	int		j;
	int		temp;
	int		temp2;

	paths = get_paths(env);
    //cmds = create_cmds();
	j = 0;
	temp2 = dup(STDIN_FILENO);
	temp = dup(STDOUT_FILENO);
    while (j < msh->groups[0]->cmds->cmd_num - 1)
    {
		cmds = msh->groups[0]->cmds->newargvs[j];
        res = exec_cmds(cmds, env, paths, msh);
       // cmds = cmds->next;
		j++;
    }
	dup2(temp, STDOUT_FILENO);
	close(temp);
	//printf("%s executed\n", cmds->content);
	cmds = msh->groups[0]->cmds->newargvs[j];
	res = exec_last(cmds, env, paths);
	dup2(temp2, STDIN_FILENO);
	close(temp2);
	return (res);
	//exit(EXIT_SUCCESS);
}

