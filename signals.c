/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:07:21 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/24 14:11:36 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void    handle_sig(int sig)
{
    printf("MIAU");
}

void    ft_signal(void)
{
    struct sigaction sa;
    
    sa.sa_handler = &handle_sig;
    
}