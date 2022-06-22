/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:05:10 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/22 09:51:51 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//A variable name in Bash can include letters, digits, and underscores. Its name can be started with a letter and an underscore, only. Valid variable names are size, tax5, and _tax20 but not 5rules.
void	free_double(char **string)
{
	int	i;

	i = 0;
	while (string[i] != NULL)
	{
		free(string[i]);
		i++;
	}
	free(string[i]);
	free(string);
}

int	check_name(char *str)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char *args)
{
	char **temp;
	int		res;

	if (!(ft_isalpha(args[0]) || args[0] == '_'))
		return (0);
	temp = ft_split(args, '=');
	res = check_name(temp[0]);
	free_double(temp);
	return (res);
}

unsigned int	env_list_size(t_env **env_list)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = *env_list;
	if (!temp)
	{
		perror("List is Empty\n");
		return (0);
	}
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	get_name_arg(t_env *new_env, char *args, t_env **env_list)
{
	char	*name;
	char	*value;
	t_env	*node;
	int		i;
	int		len;
	int		k;

	k = 0;
	i = 0;
	len = 0;
	//len name
	while (args[len] != '=')
		len++;
	name = malloc(len + 1);
	while (i < len)
	{
		name[i] = *args;
		i++;
		args++;
	}
	name[i] = '\0';
	if (!*(args + 1))
		value = "";
	else
	{
		args++;
		len = 0;
		while (args[len])
			len++;
		value = malloc(len + 1);
		while (*args)
		{
			value[k] = *args;
			k++;
			args++;
		}
		value[k] = 0;
	}
	node = find_env_node(env_list, name);
	if (node)
	{
		printf("trigger");
		node->bash_v_content = value;
		free(name);
	}
	else
	{
		new_env = malloc(sizeof(t_env));
		new_env->bash_variable = name;
		new_env->bash_v_content = value;
		new_env->sort = 2;
		new_env->next = NULL;
		ft_lstadd_back_env_element(env_list, new_env);
	}
}

int	do_export(t_env **env_list, char *args)
{
	t_env	*new_env;
	char	**temp;

	//to do:check if name is already in env
	if (!ft_strncmp(args, "0", 1))
	{
		print_sorted_export(env_list);
		return (1);
	}
	if (!ft_strchr(args, '='))
		return (0);
	if (check_args(args))
	{
		get_name_arg(new_env, args, env_list);
		return (1);
	}
	else
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd("' : not a valid identifier\n", 2);
	}
	return (0);
}
