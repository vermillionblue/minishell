/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:45:50 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/24 15:52:42 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

char	*check_if_no_args(char **args)
{
	if (!args[1])
			args[1] = "0";
	return (args[1]);
}

int	print_error(int res, char *path)
{
	if (res < 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		return (1);
	}
	return (0);
}

void up_or_down(char *home, char *path, int *res)
{
	char *temp;

	home = ft_strjoin(home, "/");
	temp = ft_strjoin(home, path);
	free(home);
	if (access(temp, F_OK) == 0 || !ft_strncmp(path, "..", 2) || access(path, F_OK) == 0)
	{
		*res = chdir(path);
		free(temp);
	}
}

void	expand_tilde(char *home, char *path, int *res)
{
	char	*temp;

	ft_memmove(path, path + 1, ft_strlen(path));
	home = ft_strjoin(home, "/");
	temp = ft_strjoin(home, path);
	*res = chdir(temp);
}

int	do_cd(char *path)
{
	char	*home;
	int		res;

	res = -1;
	home = getenv("HOME");
	if (!ft_strncmp(path, "0", 1))
		chdir(home);
	else
	{
		if (!ft_strncmp(path, "~", 1))
			expand_tilde(home, path, &res);
		else
			up_or_down(home, path, &res);
		if (print_error(res, path))
			return (0);
	}
	return (1);
}
