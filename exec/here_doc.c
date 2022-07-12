/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:23:30 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/12 15:26:22 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	*read_stdin(char *limiter, char *file)
{
	char	*line;
	int		fd;
	int		id;

	id = fork();
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (id == 0)
	{
		ft_signal_child();
		while (1)
		{
			line = readline("> ");
			printf("%s vs %s\n", limiter, line);
			if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1) || !line)
			{
				// printf("trigger\n");
				// free (limiter);
				break ;
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	wait(NULL);
	return (file);
}
