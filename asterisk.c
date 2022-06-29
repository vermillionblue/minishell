/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:28:40 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/28 19:36:11 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//cmd being e.g ls -l *M: will retrieve all files ending with M in the current dir

int	ft_regexcomp(char *regex, char *name)
{
    int	i;
    int	last;
    int	k;

    i = 0;
    k = 0;
	last = ft_strlen(regex) - 1;
	// printf("%c last char for %s\n", regex[last], regex);
    while (regex[i] && name[k])
    {
        if (regex[i] == '*')
        {
			if ((i  ==  last && name[ft_strlen(name) - 1] == regex[i]))
                return (1);

            while ((name[k] != regex[i + 1] && name[k]) || (i + 1 ==  last && name[k] && name[k] == regex[i + 1]  && name[k + 1]))
			{
				k++;
			}
			if (i  == last)
                i++;
			else
           		i +=  2;

            k++;
        }
        else if (regex[i] != name[k] && regex[i] != '*')
            return (0);
        else
        {
            i++;
            k++;
        } 
    }
    if (!regex[i] && !name[k] && name[ft_strlen(name) - 1] == regex[last])
        return (1);
    return (0);
}

void    print_regex_error(char *cmd, char *regex)
{
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(regex, 2);
    ft_putstr_fd(": No such file or directory\n", 2);
}

char    *expand_wildcard(char *raw_cmd)
{
    char	cwd[PATH_MAX];
    struct	dirent *dirp;
    char    **temp;
    char    *tmp2;
    char    *cmd;
    int     i;
    DIR     *dir;

    i = 1;
    temp = ft_split(raw_cmd, ' ');
    cmd = temp[0];

	getcwd(cwd, sizeof(cwd));
	dir = opendir(cwd);
	while ((dirp = readdir(dir)) != NULL)
    {
        if (ft_regexcomp(temp[1], dirp->d_name))
        {
            tmp2 = ft_strjoin(cmd, " ");
            cmd = ft_strjoin(tmp2, dirp->d_name);
            free(tmp2);
        }
    }
	if (closedir(dir) == -1)
        perror("closedir");
    if (!ft_strncmp(cmd, temp[0], ft_strlen(cmd + 1)))
    {
        print_regex_error(temp[0], temp[1]);
        exit(EXIT_FAILURE);
    }
    return (cmd);
}



