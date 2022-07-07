/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:28:40 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/07 12:41:49 by vangirov         ###   ########.fr       */
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
    printf("WC TEST 3\n");
	last = ft_strlen(regex) - 1;
    printf("WC TEST 4\n");
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
        printf("WC TEST 1\n");
        if (ft_regexcomp(regex_arg, dir_struct->d_name))
        {
            printf("WC TEST 2\n");
            tmp2 = ft_strjoin(cmd, " ");
            cmd = ft_strjoin(tmp2, dir_struct->d_name);
            free(tmp2);
        }
        dir_struct = readdir(dir);
    }
    return (cmd);
}

char    *expand_wildcard(char *raw_cmd)
{
    char	cwd[PATH_MAX];
    char    **temp;
    char    *cmd;
    DIR     *dir;

    temp = ft_split(raw_cmd, ' ');
    cmd = temp[0];
	getcwd(cwd, sizeof(cwd));
	dir = opendir(cwd);
    cmd = ft_read_dir(cmd, temp[1], dir);
	if (closedir(dir) == -1)
        perror("closedir");
    if (!ft_strncmp(cmd, temp[0], ft_strlen(cmd + 1)))
    {
        print_regex_error(temp[0], temp[1]);
        exit(EXIT_FAILURE);
    }
    return (cmd);
}
