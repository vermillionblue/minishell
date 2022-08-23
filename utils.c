/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:18:34 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/23 13:46:19 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*split_rev(char **cmds)
{
	int		i;
	char	*line;
	char	*temp;

	i = 1;
	temp = cmds[0];
	while (cmds[i])
	{
		line = ft_strjoin(temp, cmds[i]);
		i++;
	}
	if (i == 1)
		return (temp);
	return (line);
}

// int	ft_isspace(char c)
// {
// 	if (c == '\t' || c == '\v' || c == '\f' || c == '\n'
// 		|| c == '\r' || c == ' ')
// 		return (1);
// 	return (0);
// }

int	if_omit_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}
