/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:24:27 by danisanc          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/11 00:15:25 by danisanc         ###   ########.fr       */
=======
/*   Updated: 2022/07/11 22:43:29 by danisanc         ###   ########.fr       */
>>>>>>> dani
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

<<<<<<< HEAD
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

char	*get_correct_path(char **cmd, t_msh *msh)
{
	int		i;
	char	*a_path;
	char	*temp;

	i = 0;
	if (access(cmd[0], F_OK) == 0)
		return (cmd[0]);
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

char	**get_paths(char **env, t_msh *msh)
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
	msh->last_exit_stat = 127;
	perror("No path\n");
	exit (EXIT_FAILURE);
}


// /built ins run in parent: unset export cd exit
// exit needs to work differently
int	redirect_parent(char **cmd, t_msh *msh)
=======
int	redirect_parent(char **cmd, int cmd_num, t_msh *msh)
>>>>>>> dani
{
	int		res;

	res = -2;
	if (!ft_strncmp(cmd[0], "cd", 3))
		res = do_cd(check_if_no_args(cmd));
	else if (!ft_strncmp(cmd[0], "export", 7))
		res = do_export(msh, check_if_no_args(cmd));
	else if (!ft_strncmp(cmd[0], "unset", 6))
		res = do_unset(msh, check_if_no_args(cmd));
	else if (!ft_strncmp(cmd[0], "exit", 5) && cmd_num == 1)
	{
		msh->exit = 1;
		res = 0;
	}
	return (res);
}

int	redirect_child(char **cmd, t_msh *msh)
{
	int		res;
	char	*a_path;

	res = 0;
	if (!ft_strncmp(cmd[0], "pwd", 4))
		res = do_cwd();
	else if (!ft_strncmp(cmd[0], "env", 4))
		print_env_list(msh->env_list);
	else if (!ft_strncmp(cmd[0], "echo", 5) && is_nflag(cmd[1]))
		res = do_echo(cmd);
	// else if (!ft_strncmp(cmd[0], "history", 8))
	// {

	// }
	else if (!ft_strncmp(cmd[0], "exit", 5))
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		a_path = get_correct_path(cmd, msh);
		if (execve(a_path, cmd, msh->env) == -1)
		{
			perror("execve error\n");
			exit (EXIT_FAILURE);
		}
	}
	return (res);
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
			dup2(cmd->infile_fd, STDIN_FILENO);
	}
	if (cmd->outfile_name) 
	{
		if (cmd->append_outfile)
			cmd->outfile_fd = open(cmd->outfile_name, O_WRONLY
			| O_CREAT | O_APPEND, 0664);
		else
			cmd->outfile_fd = open(cmd->outfile_name, O_WRONLY
			| O_CREAT | O_TRUNC, 0664);
	}
}

int	exec_cmds(char **cmd, t_group *group, t_msh *msh)
{
	int		fd[2];
	int		res;
    int		id;

	set_std_i_o(group->cmds, msh);
    check_pipe(pipe(fd));
	id = fork();
	if (id == 0)
	{
		ft_signal_child();
		if (group->cmds->cmd_num == 1)
		{
			close(fd[READ_END]);
			close(fd[WRITE_END]);
			if (group->cmds->outfile_name)
			{
				check_dup(dup2(group->cmds->outfile_fd, STDOUT_FILENO));
				close(group->cmds->outfile_fd);
			}
			else
			{
				check_dup(dup2(msh->temp_i_o[WRITE_END], STDOUT_FILENO));
				close(msh->temp_i_o[WRITE_END]);
			}
		}
		else
		{
			close(fd[READ_END]);
			check_dup(dup2(fd[WRITE_END], STDOUT_FILENO));
			close(fd[WRITE_END]);
		}
		redirect_child(cmd, msh);
	}
	if (group->cmds->cmd_num == 1)
	{
		close(fd[WRITE_END]);
		close(fd[READ_END]);
		close(group->cmds->infile_fd);
		check_dup(dup2(msh->temp_i_o[READ_END], STDIN_FILENO));
		close(msh->temp_i_o[READ_END]);
	}
	else
	{
		close(fd[WRITE_END]);
		check_dup(dup2(fd[READ_END], STDIN_FILENO));
		close(fd[READ_END]);
	}
	waitpid(0, &res, 0);
	return (res);
}

void	exec_group(t_group *group, t_msh *msh)
{
	int	j;
	int	cmd_num;
	int	res;

	j = 0;
	res = 0;
	cmd_num = group->cmds->cmd_num;
	msh->temp_i_o = malloc(sizeof(int) * 2);
	check_dup(msh->temp_i_o[READ_END] = dup(STDIN_FILENO));
	check_dup(msh->temp_i_o[WRITE_END] = dup(STDOUT_FILENO));
    while (group->cmds->cmd_num > 0)
    {
		if (group->cmds->redirs[j][0])
		{
			while (group->cmds->redirs[j][0])
			{
				check_infile(group, msh, j);
				check_outfile(group, j);
				group->cmds->redirs[j][0] = group->cmds->redirs[j][0]->next;
			}
		}
		res = redirect_parent(group->cmds->newargvs[j], cmd_num, msh);
		if (res == -2)
        	msh->last_exit_stat = exec_cmds(group->cmds->newargvs[j], group, msh);
		else
			msh->last_exit_stat = res;
		group->cmds->cmd_num  -= 1; 
		j++;
    }
}

void	ft_prep_exec(t_msh *msh, t_env **env_list)
{
	int	i;
	char **env;
	char **env_temp;

	i 	= 0;
	env = list_to_arr(env_list);
	env_temp = list_to_arr(env_list);
	msh->env = env;
	msh->paths = get_paths(env_temp, msh);
	msh->last_exit_stat = 0;
	msh->env_list = env_list;
	while(msh->group_num > i)
	{
		if (msh->groups[i]->type == LX_AND && msh->last_exit_stat > 0)
			break ;
		if (msh->groups[i]->type == LX_OR && msh->last_exit_stat == 0)
			break ;
		exec_group(msh->groups[i], msh);
		i++;
	}
}
