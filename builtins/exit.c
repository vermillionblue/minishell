/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:17:49 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 13:09:59 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	do_exit(void)
{
	printf(BLUE);
	printf("Exiting... 🥲\n");
	printf(WHITE);
	exit(EXIT_SUCCESS);
}

int	exit_many_args(t_msh *msh)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd("too many arguments\n", 2);
	msh->last_exit_stat = 127;
	return (127);
}

int	exit_helper(char **cmd, t_msh *msh, int cmd_num)
{
	int	k;

	k = 0;
	if (cmd[2])
		return (exit_many_args(msh));
	if (cmd[1])
	{
		while (cmd[1][k])
		{
			if (!ft_isdigit(cmd[1][k]))
			{
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(cmd[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				return (127);
			}
			k++;
		}
		return (ft_atoi(cmd[1]));
	}
	if (cmd_num == 1 && !cmd[1])
		msh->exit = 1;
	return (0);
}
