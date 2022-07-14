/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:24:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/15 00:00:51 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	redirect_parent(char **cmd, int cmd_num, t_msh *msh)
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
	else if (!ft_strncmp(cmd[0], "exit", 5))
		do_exit();
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

int	exec_cmds(char **cmd, t_group *group, t_msh *msh)
{
	int		res;
    int		id;

	msh->pipe_fds = malloc(sizeof(int) * 2);
	set_std_i_o(group->cmds, msh);
    check_pipe(pipe(msh->pipe_fds));
	id = fork();
	if (id == 0)
	{
		ft_signal_child();
		close_fds_child(group, msh);
		redirect_child(cmd, msh);
	}
	close_fds_parent(group, msh);
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
	msh->here_doc_file_name = ".here_doc";
	msh->env = env;
	msh->paths = get_paths(env_temp, msh);
	msh->last_exit_stat = 0;
	msh->env_list = env_list;
	while (msh->group_num > i)
	{
		ft_parse_group(msh, i);
		if (msh->groups[i]->type == LX_AND && msh->last_exit_stat > 0)
			break ;
		if (msh->groups[i]->type == LX_OR && msh->last_exit_stat == 0)
			break ;
		exec_group(msh->groups[i], msh);
		i++;
	}
}
