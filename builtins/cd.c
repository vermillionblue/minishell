/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 23:45:50 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/03 16:27:40 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include "builtins.h"

void	print_error(int res, char *path)
{
	if (res < 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
	}
}

void do_cd(char *path)
{
	char	cwd[PATH_MAX];
	int		len;
	char	*home;
	int		res;
	char	*temp;

	home = getenv("HOME");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
      perror("getcwd() error");
	if (!ft_strncmp(path, "0", 1))
		chdir(home);
	else
	{
		if (!ft_strncmp(path, "~", 1))
		{
			ft_memmove(path, path + 1, ft_strlen(path));
			home = ft_strjoin(home, "/");
			temp = ft_strjoin(home, path);
			res = chdir(temp);
		}
		else
		{
			home = ft_strjoin(home, "/");
			temp = ft_strjoin(home, path);
			free(home);
			if (access(temp, F_OK) == 0 || !ft_strncmp(path, "..", 2) || access(path, F_OK) == 0)
			{
				res = chdir(path);
				free(temp);

			}
		}
		print_error(res, path);
	}
}
