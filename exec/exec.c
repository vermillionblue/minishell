/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:24:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/11 19:41:09 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	redirect_parent(char **cmd, t_msh *msh)
{
	int		res;

	res = -2;
	if (!ft_strncmp(cmd[0], "cd", 3))
		res = do_cd(check_if_no_args(cmd));
	else if (!ft_strncmp(cmd[0], "export", 7))
		res = do_export(msh, check_if_no_args(cmd));
	else if (!ft_strncmp(cmd[0], "unset", 6))
		res = do_unset(msh, check_if_no_args(cmd));
	// else if (!ft_strncmp(cmd[0], "exit", 5))
	// 	do_exit();
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
	// else if (!ft_strncmp(cmd[0], "echo", 5) && !ft_strncmp(args[1], "-n", 3))
	// 	res = do_echo(args);
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
	int	res;

	j = 0;
	res = 0;
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
		res = redirect_parent(group->cmds->newargvs[j], msh);
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
