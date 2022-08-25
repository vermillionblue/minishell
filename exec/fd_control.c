/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:01:08 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/25 19:55:33 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	check_open_fail(int i, t_msh *msh)
{
	if (i == -1)
	{
		msh->open_stat = 0;
		perror("sorry, cannot open file\n");
		msh->last_exit_stat = 1;
	}
	return (i);
}

int	set_std_i_o(t_cmds *cmd, t_msh *msh)
{
	msh->open_stat = 1;
	if (cmd->infile_name)
	{
		cmd->infile_fd = check_open_fail(open(cmd->infile_name, O_RDONLY), msh);
		if (cmd->infile_fd == -1)
		{
			perror(cmd->infile_name);
			msh->last_exit_stat = 1;
			return (0);
		}
		else
			check_dup2(dup2(cmd->infile_fd, STDIN_FILENO));
	}
	if (cmd->outfile_name)
	{
		if (cmd->append_outfile)
			cmd->outfile_fd = check_open_fail(open(cmd->outfile_name,
						O_WRONLY | O_CREAT | O_APPEND, 0664), msh);
		else
			cmd->outfile_fd = check_open_fail(open(cmd->outfile_name,
						O_WRONLY | O_CREAT | O_TRUNC, 0664), msh);
	}
	return (msh->open_stat);
}

void	fds_child_last_cmd(t_msh *msh, t_group *group)
{
	close(msh->pipe_fds[READ_END]);
	close(msh->pipe_fds[WRITE_END]);
	if (group->cmds->infile_name != NULL)
	{
		check_dup2(dup2(group->cmds->infile_fd, STDIN_FILENO));
		close(group->cmds->infile_fd);
	}	
	if (group->cmds->outfile_name)
	{
		check_dup2(dup2(group->cmds->outfile_fd, STDOUT_FILENO));
		close(group->cmds->outfile_fd);
	}
	else
		check_dup2(dup2(msh->temp_i_o[WRITE_END], STDOUT_FILENO));
	if (access(msh->here_doc_file_name, F_OK) == 0)
		unlink(msh->here_doc_file_name);
	close(msh->temp_i_o[WRITE_END]);
	close(msh->temp_i_o[READ_END]);
}

void	close_fds_child(t_group *group, t_msh *msh, int cmd_num)
{
	if (cmd_num == 1)
		fds_child_last_cmd(msh, group);
	else
	{
		close(msh->pipe_fds[READ_END]);
		if (group->cmds->outfile_name)
		{
			check_dup2(dup2(group->cmds->outfile_fd, STDOUT_FILENO));
			close(group->cmds->outfile_fd);
		}
		else
			check_dup2(dup2(msh->pipe_fds[WRITE_END], STDOUT_FILENO));
		close(msh->pipe_fds[WRITE_END]);
	}
}

void	close_fds_parent(t_group *group, t_msh *msh, int cmd_num)
{
	if (cmd_num == 1)
	{
		close(msh->temp_i_o[WRITE_END]);
		close(msh->pipe_fds[WRITE_END]);
		close(msh->pipe_fds[READ_END]);
		if (group->cmds->infile_name)
			close(group->cmds->infile_fd);
		if (group->cmds->outfile_name)
			close(group->cmds->outfile_fd);
		check_dup2(dup2(msh->temp_i_o[READ_END], STDIN_FILENO));
		close(msh->temp_i_o[READ_END]);
	}
	else
	{
		close(msh->pipe_fds[WRITE_END]);
		check_dup2(dup2(msh->pipe_fds[READ_END], STDIN_FILENO));
		close(msh->pipe_fds[READ_END]);
	}
}
