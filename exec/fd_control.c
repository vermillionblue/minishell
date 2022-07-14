/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 14:01:08 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/14 21:25:11 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	set_std_i_o(t_cmds *cmd, t_msh *msh)
{
	if (cmd->infile_name != NULL)
	{
		cmd->infile_fd = open(cmd->infile_name, O_RDONLY);
		if (cmd->infile_fd == -1)
		{
			printf("trigger\n");
			perror(cmd->infile_name);
			msh->last_exit_stat = 1;
			return (0);
		}
		else
			dup2(cmd->infile_fd, STDIN_FILENO);
	}
	if (cmd->outfile_name)
	{
		if (cmd->append_outfile)
			cmd->outfile_fd = open(cmd->outfile_name,
					O_WRONLY | O_CREAT | O_APPEND, 0664);
		else
			cmd->outfile_fd = open(cmd->outfile_name,
					O_WRONLY | O_CREAT | O_TRUNC, 0664);
	}
	return (1);
}

void	close_fds_child(t_group *group, t_msh *msh)
{
	if (group->cmds->cmd_num == 1)
	{
		close(msh->pipe_fds[READ_END]);
		close(msh->pipe_fds[WRITE_END]);
		if (group->cmds->outfile_name)
		{
			check_dup2(dup2(group->cmds->outfile_fd, STDOUT_FILENO));
			close(group->cmds->outfile_fd);
		}
		else
			check_dup2(dup2(msh->temp_i_o[WRITE_END], STDOUT_FILENO));
		if (group->cmds->infile_name)
			close(group->cmds->infile_fd);
		close(msh->temp_i_o[WRITE_END]);
		close(msh->temp_i_o[READ_END]);
		if (group->cmds->here_doc)
			unlink(msh->here_doc_file_name);
	}
	else
	{
		close(msh->pipe_fds[READ_END]);
		check_dup2(dup2(msh->pipe_fds[WRITE_END], STDOUT_FILENO));
		close(msh->pipe_fds[WRITE_END]);
	}
}

void	close_fds_parent(t_group *group, t_msh *msh)
{
	if (group->cmds->cmd_num == 1)
	{
		if (group->cmds->infile_name)
			close(group->cmds->infile_fd);
		if (group->cmds->outfile_name)
			close(group->cmds->outfile_fd);
		close(msh->pipe_fds[WRITE_END]);
		close(msh->pipe_fds[READ_END]);
		check_dup2(dup2(msh->temp_i_o[READ_END], STDIN_FILENO));
		close(msh->temp_i_o[READ_END]);
		close(msh->temp_i_o[WRITE_END]);
	}
	else
	{
		close(msh->pipe_fds[WRITE_END]);
		check_dup2(dup2(msh->pipe_fds[READ_END], STDIN_FILENO));
		close(msh->pipe_fds[READ_END]);
	}
}
