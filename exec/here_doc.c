/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:23:30 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 14:10:30 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	read_in_child(char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1) || !line)
		{
			free (limiter);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

char	*read_stdin(char *limiter, char *file)
{
	int		fd;
	int		id;

	id = fork();
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (id == 0)
	{
		ft_signal_child();
		read_in_child(limiter, fd);
	}
	wait(NULL);
	return (file);
}
