/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:24:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 14:54:39 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	redirect_parent(char **cmd, int cmd_num, t_msh *msh)
{
	int		res;

	res = -2;
	if (!ft_strncmp(cmd[0], "cd", 3))
		res = do_cd(cmd[1]);
	else if (!ft_strncmp(cmd[0], "export", 7))
		res = do_export(msh, cmd[1]);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		res = do_unset(msh, cmd[1]);
	else if (!ft_strncmp(cmd[0], "exit", 5))
	{
		if (cmd_num == 1 && !cmd[1])
		{
			res = 0;
			msh->exit = 1;
		}
	}
	return (res);
}

int	redirect_child(char **cmd, t_msh *msh)
{
	int		res;

	res = 0;
	if (!ft_strncmp(cmd[0], "pwd", 4))
		res = do_cwd();
	else if (!ft_strncmp(cmd[0], "env", 4))
		print_env_list(msh->env_list);
	else if (!ft_strncmp(cmd[0], "echo", 5))
		res = do_echo(cmd);
	else if (!ft_strncmp(cmd[0], "exit", 5))
		res = exit_helper(cmd, msh, 3);
	else
		ft_execve(cmd, msh);
	ft_free_exec(msh);
	exit (res);
}

int	exec_cmds(char **cmd, t_group *group, t_msh *msh, int cmd_num)
{
	int		res;
	int		id;
	char	**env_temp;

	env_temp = list_to_arr(msh->env_list);
	msh->paths = get_paths(env_temp);
	free_double(env_temp);
	msh->pipe_fds = ft_calloc(2, sizeof(int));
	check_pipe(pipe(msh->pipe_fds));
	if (!set_std_i_o(group->cmds, msh))
		return (0);
	id = fork();
	if (id == 0)
	{
		ft_signal_child();
		close_fds_child(group, msh, cmd_num);
		redirect_child(cmd, msh);
	}
	waitpid(0, &res, 0);
	close_fds_parent(group, msh, cmd_num);
	if (msh->paths)
		free_double(msh->paths);
	free(msh->pipe_fds);
	return (res);
}

void	exec_group(t_group *group, t_msh *msh)
{
	int	j;
	int	cmd_num;

	j = 0;
	cmd_num = group->cmds->cmd_num;
	init_data4group(msh);
	while (cmd_num > 0)
	{
		if (ft_ectracttype(group->cmds->cmd_args[j][0]) == LX_PAR)
			msh->last_exit_stat
				= ft_subshell(split_rev(group->cmds->newargvs[j]), msh->env);
		else
			builtin_or_exec(group, msh, cmd_num, j);
		cmd_num -= 1;
		j++;
	}
}

void	ft_prep_exec(t_msh *msh)
{
	int		i;
	char	**env;

	i = 0;
	env = NULL;
	env = list_to_arr(msh->env_list);
	msh->here_doc_file_name = ".here_doc";
	msh->env = env;
	while (msh->group_num > i)
	{
		ft_parse_group(msh, i);
		if (!msh->groups[0]->cmds->newargvs
			|| (msh->group_num == 1 && !msh->groups[0]->cmds->newargvs[0]))
			return ;
		if (msh->groups[i]->type == LX_AND && msh->last_exit_stat > 0)
			break ;
		if (msh->groups[i]->type == LX_OR && msh->last_exit_stat == 0)
			break ;
		exec_group(msh->groups[i], msh);
		free(msh->temp_i_o);
		i++;
	}
}
