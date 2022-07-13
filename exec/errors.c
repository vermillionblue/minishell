/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:04:10 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/13 18:06:15 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	check_dup(int n)
{
	if (n < 0)
	{	
		perror("dup error\n");
		exit(EXIT_FAILURE);
	}
}

void	check_dup2(int n)
{
	if (n < 0)
	{	
		perror("dup2 error\n");
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
