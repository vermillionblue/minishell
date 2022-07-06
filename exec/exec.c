/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:24:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/06 17:23:51 by danisanc         ###   ########.fr       */
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

// int	ft_redirect(t_msh *msh, t_env *env_list, char **env)
// {
// 	char	**args;
// 	int		res;
	
// 	res = 0;
// 	args = msh->groups[0]->cmds->newargvs[0];
// 	printf("===========result=================================\n");
// 	if (!ft_strncmp(args[0], "cd", 3))
// 		res = do_cd(check_if_no_args(args));
// 	else if (!ft_strncmp(args[0], "pwd", 4))
// 		res = do_cwd();
// 	else if (!ft_strncmp(args[0], "env", 4))
// 		print_env_list(&env_list);
// 	else if (!ft_strncmp(args[0], "export", 7))
// 		res = do_export(&env_list, check_if_no_args(args));
// 	else if (!ft_strncmp(args[0], "unset", 6))
// 		res = do_unset(&env_list, check_if_no_args(args));
// 	else if (!ft_strncmp(args[0], "exit", 5))
// 		do_exit();
// 	else if (!ft_strncmp(args[0], "echo", 5) && !ft_strncmp(args[1], "-n", 3))
// 		res = do_echo(args);
// 	else
// 		prep_groups(env, msh);
// 	return (res);
// }

char	*get_correct_path(char **cmd, t_msh *msh)
{
	int		i;
	char	*a_path;
	char	*temp;

	i = 0;
	while (msh->paths[i])
	{
		temp = ft_strjoin(msh->paths[i], "/");
		a_path = ft_strjoin(temp, cmd[0]);
		if (access(a_path, F_OK) == 0)
			return (a_path);
		i++;
	}
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n ", 2);
	msh->last_exit_stat = 127;
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
	perror("no path\n");
	exit (EXIT_FAILURE);
}

void	if_dup_fail(int n)
{
	if (n < 0)
	{
		perror("dup error\n");
		exit(EXIT_FAILURE);
	}
}

void	check_pipe(int n)
{
	if (n < 0)
	{
		perror("pipe() error\n");
		exit(EXIT_FAILURE);
	}
}

int	exec_cmds(char **cmd, t_group *group, t_msh *msh)
{
	int		fd[2];
	int		res;
    int		id;
	char	*a_path;

    check_pipe(pipe(fd));
	id = fork();
	if (id == 0)
	{
		ft_signal_child();
		a_path = get_correct_path(cmd, msh);
		if (group->cmds->cmd_num == 1)
		{
			close(fd[READ_END]);
			close(fd[WRITE_END]);
			if_dup_fail(dup2(msh->temp_i_o[WRITE_END], STDOUT_FILENO));
			close(msh->temp_i_o[WRITE_END]);
		}
		else
		{
			close(fd[READ_END]);
			if_dup_fail(dup2(fd[WRITE_END], STDOUT_FILENO));
			close(fd[WRITE_END]);
		}
		if (execve(a_path, cmd, msh->env) == -1)
		{
			perror("execve\n");
			msh->last_exit_stat = 127;
			exit (EXIT_FAILURE);
		}
	}
	if (group->cmds->cmd_num == 1)
	{
		close(fd[WRITE_END]);
		close(fd[READ_END]);
		if_dup_fail(dup2(msh->temp_i_o[READ_END], STDIN_FILENO));
		close(msh->temp_i_o[READ_END]);
	}
	else
	{
		close(fd[WRITE_END]);
		if_dup_fail(dup2(fd[READ_END], STDIN_FILENO));
		close(fd[READ_END]);
	}
	waitpid(0, &res, 0);
	return (res);
}

void	exec_group(t_group *group, t_msh *msh)
{
	int		res;
	int		j;
	char	*fname;
	int		type;
	
	j = 0;
	//fname = ft_ectracttext(msh->groups[0]->cmds->redirs[0][0]);
	// type = ft_ectracttype(msh->groups[0]->cmds->redirs[0][0]);
	// printf("redir type is %d and %s name\n", type, fname);
	if_dup_fail(msh->temp_i_o[READ_END] = dup(STDIN_FILENO));
	if_dup_fail(msh->temp_i_o[WRITE_END] = dup(STDOUT_FILENO));
    while (group->cmds->cmd_num > 0)
    {
        msh->last_exit_stat = exec_cmds(group->cmds->newargvs[j], group, msh);
		group->cmds->cmd_num  -= 1; 
		j++;
    }
}
//try
//ls |cat -e && ls -l | cat | cat
void	ft_prep_exec(t_msh *msh, char **env)
{
	int	i;

	i = 0;
	msh->env = env;
	msh->paths = get_paths(env);;
	msh->last_exit_stat = -1;
	printf("===========result=================================\n");
	while(msh->group_num > i)
	{
		if (msh->groups[i]->type == LX_AND && msh->last_exit_stat == 127)
			break ;
		if (msh->groups[i]->type == LX_OR && msh->last_exit_stat == 0)
			break ;
		exec_group(msh->groups[i], msh);
		i++;
	}
}