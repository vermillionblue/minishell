/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:17:49 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/11 18:15:35 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	do_exit(void)
{
	printf(BLUE);
	printf("Exiting... 🥲\n");
	exit(EXIT_SUCCESS);
}
