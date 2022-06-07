/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:22:44 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/24 00:04:09 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_fork(int id)
{
	if (id == -1)
	{
		perror("Couldn't fork()");
		exit (EXIT_FAILURE);
	}
}

void	check_pipe(int fd)
{
	if (fd == -1)
	{
		perror("Couldn't pipe()");
		exit (EXIT_FAILURE);
	}
}
