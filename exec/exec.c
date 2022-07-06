/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:24:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/06 21:32:47 by vangirov         ###   ########.fr       */
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
		prep_groups(env, msh);
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

void	if_dup_fail(int n)
{
	if (n < 0)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
}

int	exec_cmds(char **cmd, char **env, char **paths, t_group *group, int *temps)
{
	int		fd[2];
    int		id;
	char	*a_path;

    pipe(fd);
	id = fork();
	if (id == 0)
	{
		a_path = get_correct_path(paths, cmd);
		if (group->cmds->cmd_num == 1)
		{
			close(fd[READ_END]);
			close(fd[WRITE_END]);
			if_dup_fail(dup2(temps[WRITE_END], STDOUT_FILENO));
			close(temps[WRITE_END]);
		}
		else
		{
			close(fd[READ_END]);
			if_dup_fail(dup2(fd[WRITE_END], STDOUT_FILENO));
			close(fd[WRITE_END]);
		}
		if (execve(a_path, cmd, env) == -1)
		{
			perror("execve\n");
			exit (EXIT_FAILURE);
		}
	}
	if (group->cmds->cmd_num == 1)
	{
		close(fd[WRITE_END]);
		close(fd[READ_END]);
		if_dup_fail(dup2(temps[READ_END], STDIN_FILENO));
		close(temps[READ_END]);
	}
	else
	{
		close(fd[WRITE_END]);
		if_dup_fail(dup2(fd[READ_END], STDIN_FILENO));
		close(fd[READ_END]);
	}
	waitpid(-1, NULL, 0);
	return (0); //////// otherwise:  error: control reaches end of non-void function
}

int	exec_group(t_group *group, char **env, t_msh *msh)
{
    char  **cmds;
	char	**paths;
	int		res;
	int		j;
	int		temps[2];
	// char	*fname;
	// int		type;

	paths = get_paths(env);
	j = 0 * msh->group_num; /////////// otherwise: error: unused parameter ‘msh’
	// fname = ft_ectracttext(msh->groups[0]->cmds->redirs[0][0]);
	// type = ft_ectracttype(msh->groups[0]->cmds->redirs[0][0]);
	// printf("redir type is %d and %s name\n", type, fname);
	temps[0] = dup(STDIN_FILENO);
	temps[1] = dup(STDOUT_FILENO);
    while (group->cmds->cmd_num > 0)
    {
		cmds = group->cmds->newargvs[j];
        res = exec_cmds(cmds, env, paths, group, temps);
		group->cmds->cmd_num  -= 1;
		j++;
    }
	return (res);
}

void	prep_groups(char **env, t_msh *msh)
{
	int	i;

	i = 0;
	while(msh->group_num > i)
	{
		exec_group(msh->groups[i], env, msh);
		i++;
	}
}
