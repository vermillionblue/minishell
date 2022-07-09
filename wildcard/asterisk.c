/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:28:40 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/09 12:12:11 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asterisk.h"

//cmd being e.g ls -l *M: will retrieve all files ending with M in the current dir
void    for_asterisk(char *regex, char *name, int *i, int *k)
{
    while(regex[*i + 1] == '*')
        *i = *i + 1;
    while ((name[*k] != regex[*i + 1] && name[*k]))
        *k = *k + 1;
    *i = *i + 2;
	*k = *k + 1;
}

int if_return(char *name, char *regex, int k, int i)
{
    int	last;

    last = ft_strlen(regex) - 1;
    if (!name[k] && regex[i] == '*' && i == last)
        return (1);    
    if (!name[k] && regex[i])
        return (0);
    if (regex[i] != name[k])
        return (0);
    if (!regex[i] && !name[k])
        return (1);
    return (2);
}

int	ft_regexcomp(char *regex, char *name)
{
    int	i;
    int	last;
    int	k;

    i = 0;
    k = 0;
	last = ft_strlen(regex) - 1;
    while (regex[i] && name[k])
    {
        if ((regex[i] == '*' && i + 1 == last &&
        name[ft_strlen(name) - 1] == regex[last]) || (i == last && regex[i] == '*'))
           return (1);
        else if (regex[i] == '*')
			for_asterisk(regex, name, &i, &k);
		else if(if_return(name, regex, k, i) != 2)
			return (if_return(name, regex, k, i));
        else
        {
            i++;
            k++;
        }
    }
    return (0);
}

char *ft_read_dir(char *cmd, char *regex_arg, DIR *dir)
{
    struct	dirent *dir_struct;
    char    *tmp2;

    dir_struct = readdir(dir);
	while (dir_struct != NULL)
    {
        if (ft_regexcomp(regex_arg, dir_struct->d_name))
        {
            tmp2 = ft_strjoin(cmd, " ");
            cmd = ft_strjoin(tmp2, dir_struct->d_name);
            free(tmp2);
        }
        dir_struct = readdir(dir);
    }
    return (cmd);
}

char    *expand_wildcard(char *arg)
{
    char	cwd[PATH_MAX];
    char    *cmd;
    DIR     *dir;

    cmd = arg;
	getcwd(cwd, sizeof(cwd));
	dir = opendir(cwd);
    cmd = ft_read_dir(cmd, arg, dir);
	if (closedir(dir) == -1)
        perror("closedir() error\n");
    return (cmd);
}
