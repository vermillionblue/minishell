/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:24:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/09 17:04:22 by danisanc         ###   ########.fr       */
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

char	*read_stdin(char *limiter, char *file)
{
	char	*line;
	int		fd;
	int		id;

	id = fork();
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (id == 0)
	{
		ft_signal_child();
		while (1)
		{
			line = readline("> ");
			if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1) || !line)
			{
				free (limiter);
				break ;
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	wait(NULL);
	return (file);
}


// int	redirect_child(char *a_path, char **cmd, t_msh *msh)
// {
// 	int		res;

// 	res = 0;
// 	if (!ft_strncmp(cmd[0], "pwd", 4))
// 		res = do_cwd();
// 	else if (!ft_strncmp(cmd[0], "env", 4))
// 		print_env_list(msh->env_list);
// 	// else if (!ft_strncmp(args[0], "echo", 5) && !ft_strncmp(args[1], "-n", 3))
// 	// 	res = do_echo(args);
// 	else
// 	{
// 		if (execve(a_path, cmd, msh->env) == -1)
// 		{
// 			perror("execve error\n");
// 			msh->last_exit_stat = 1;
// 			exit (EXIT_FAILURE);
// 		}
// 	}
// // 	return (res);
// // }

// ///built ins run in parent: unset export cd exit
// //exit needs to work differently
// int	redirect_parent(t_msh *msh, t_env *env_list)
// {
// 	int		res;
// 	char	*args;

// 	res = -2;
// 	args = msh->groups[0]->cmds->newargvs[0];
// 	if (!ft_strncmp(args[0], "cd", 3))
// 		res = do_cd(check_if_no_args(args));
// 	else if (!ft_strncmp(args[0], "export", 7))
// 		res = do_export(&env_list, check_if_no_args(args));
// 	else if (!ft_strncmp(args[0], "unset", 6))
// 		res = do_unset(&env_list, check_if_no_args(args));
// 	else if (!ft_strncmp(args[0], "exit", 5))
// 		do_exit();
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
	return (NULL);
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
	return (NULL);
	//exit (EXIT_FAILURE);
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

void	set_std_i_o(t_cmds *cmd, t_msh *msh)
{
	if (cmd->infile_name)
	{
		cmd->infile_fd = open(cmd->infile_name, O_RDONLY);
		if (cmd->infile_fd == -1)
		{
			perror(cmd->infile_name);
			msh->last_exit_stat = 1;
		}
		else
		{
			dup2(cmd->infile_fd, STDIN_FILENO);
		}	
	}
	if (cmd->outfile_name) 
	{
		if (cmd->append_outfile)
			cmd->outfile_fd = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
		else
			cmd->outfile_fd = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	}
}

int	exec_cmds(char **cmd, t_group *group, t_msh *msh)
{
	int		fd[2];
	int		res;
    int		id;
	char	*a_path;

	set_std_i_o(group->cmds, msh);
    check_pipe(pipe(fd));
	id = fork();
	if (id == 0)
	{
		ft_signal_child();
		a_path = get_correct_path(cmd, msh);
		if (group->cmds->cmd_num == 1)
		{
			//close(group->cmds->infile_fd);
			close(fd[READ_END]);
			close(fd[WRITE_END]);
			if (group->cmds->outfile_name)
			{
				if_dup_fail(dup2(group->cmds->outfile_fd, STDOUT_FILENO));
				close(group->cmds->outfile_fd);
			}
			else
			{
				if_dup_fail(dup2(msh->temp_i_o[WRITE_END], STDOUT_FILENO));
				close(msh->temp_i_o[WRITE_END]);
			}
		}
		else
		{
			close(fd[READ_END]);
			if_dup_fail(dup2(fd[WRITE_END], STDOUT_FILENO));
			close(fd[WRITE_END]);
		}
		//redirect_child(a_path, cmd, msh);
		if (execve(a_path, cmd, msh->env) == -1)
		{
			perror("execve error\n");
			msh->last_exit_stat = 1;
			exit (EXIT_FAILURE);
		}
	}
	if (group->cmds->cmd_num == 1)
	{
		close(fd[WRITE_END]);
		close(fd[READ_END]);
		close(group->cmds->infile_fd);
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
	int	j;

	j = 0;
	msh->temp_i_o = malloc(sizeof(int) * 2);
	if_dup_fail(msh->temp_i_o[READ_END] = dup(STDIN_FILENO));
	if_dup_fail(msh->temp_i_o[WRITE_END] = dup(STDOUT_FILENO));
    while (group->cmds->cmd_num > 0)
    {
		if (group->cmds->redirs[j][0])
		{
			while (group->cmds->redirs[j][0])
			{
				if (ft_ectracttype(group->cmds->redirs[j][0]) == LX_REDIR_IN ||
				ft_ectracttype(group->cmds->redirs[j][0]) == LX_REDIR_INSRC)
				{
					
					if (ft_ectracttype(group->cmds->redirs[j][0]) == LX_REDIR_INSRC)
					{
						group->cmds->here_doc = 1;
						read_stdin(ft_ectracttext(group->cmds->redirs[j][0]), ".here_doc");
						group->cmds->infile_name = ".here_doc";
					}	
					else
					{
						group->cmds->here_doc = 0;
						group->cmds->infile_name = ft_ectracttext(group->cmds->redirs[j][0]);
					}
				}
				else if (ft_ectracttype(group->cmds->redirs[j][0]) == LX_REDIR_OUT || ft_ectracttype(group->cmds->redirs[j][0]) == LX_REDIR_APPEND)
				{
					group->cmds->outfile_name = ft_ectracttext(group->cmds->redirs[j][0]);
					if (ft_ectracttype(group->cmds->redirs[j][0]) == LX_REDIR_APPEND)
						group->cmds->append_outfile = 1;
					else
						group->cmds->append_outfile = 0;
				}	
				group->cmds->redirs[j][0] = group->cmds->redirs[j][0]->next;
			}
		}
		// res = redirect_parent(msh)
		// if ()
        msh->last_exit_stat = exec_cmds(group->cmds->newargvs[j], group, msh);
		group->cmds->cmd_num  -= 1; 
		j++;
    }
}
//try
//<in <innn ls | <i <ll ls && <k <kjn ls // test in out files
//ls |cat -e & ls -l | cat | cat // tes logical ops
void	ft_prep_exec(t_msh *msh, t_env **env_list)
{
	int	i;

	i = 0;
	msh->env = list_to_arr(env_list);
	msh->paths = get_paths(list_to_arr(env_list));
	msh->last_exit_stat = 0;
	msh->env_list = env_list;
	printf("===========result===========\n");
	while(msh->group_num > i)
	{
		if (msh->groups[i]->type == LX_AND && msh->last_exit_stat > 0)
			break ;
		if (msh->groups[i]->type == LX_OR && msh->last_exit_stat == 0)
			break ;
		exec_group(msh->groups[i], msh);
		//msh->groups[i]->cmds->redirs[0][k]
		i++;
	}
}