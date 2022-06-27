/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:28:40 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/27 19:24:25 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//cmd being e.g ls -l *M: will retrieve all files ending with M in the current dir
t_list *get_filenames()
{
    char	cwd[PATH_MAX];
    t_list  *dir_list;
    t_list  *current;
    struct	dirent *dirp;
    DIR	*dir;

    dir_list = NULL;
	getcwd(cwd, sizeof(cwd));
	dir = opendir(cwd);
	while ((dirp = readdir(dir)) != NULL)
    {
        current = malloc(sizeof(t_list));
        current->content = dirp->d_name;
        current->next = NULL;
        ft_lstadd_back(&dir_list, current);
    }
	if (closedir(dir) == -1)
        perror("closedir");
    return (dir_list);
}



