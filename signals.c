/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:07:21 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/20 18:48:34 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	handle_sigtint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_redisplay();
}

void	ft_signal_parent(void)
{
	signal(SIGINT, &handle_sigtint);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
