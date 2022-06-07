/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:17:49 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/05 23:51:38 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void do_exit(void)
{
	printf(BLUE);
	printf("Exiting... 🥲\n");
	exit(EXIT_SUCCESS);
}
