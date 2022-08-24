/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:23:30 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 20:55:57 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	read_in_child(t_msh *msh, char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(limiter, line, ft_strlen(limiter) + 1) || !line)
		{
			if (line)
				free(line);
			free (limiter);
			ft_free_msh(msh);
			free(msh->temp_i_o);
			free_double(msh->env);
			free(msh->delims);
			free_env_list(msh->env_list);
			exit (EXIT_SUCCESS);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

char	*read_stdin(t_msh *msh, char *limiter, char *file)
{
	int		fd;
	int		id;

	id = fork();
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (id == 0)
	{
		ft_signal_child();
		read_in_child(msh, limiter, fd);
	}
	wait(NULL);
	free(limiter);
	return (file);
}
