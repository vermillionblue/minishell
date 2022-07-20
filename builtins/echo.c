/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:08:34 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/16 13:45:38 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	is_nflag(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i++] == '-')
	{
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

int	do_echo(char **args)
{
	int	i;
	int	first;

	first = 1;
	if (is_nflag(args[1]))
		i = 2;
	else
		i = 1;
	while (args[i])
	{
		if (first)
			first = 0;
		else
			printf(" ");
		printf("%s", args[i++]);
	}
	if (!is_nflag(args[1]))
		printf("\n");
	return (0);
}
