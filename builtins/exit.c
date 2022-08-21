/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:17:49 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/21 14:02:50 by danisanc         ###   ########.fr       */
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
