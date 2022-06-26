/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:05:10 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/26 20:01:30 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

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

int	check_if_valid_env(char *name)
{
	int	i;

	i = 1;
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
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

char	*get_content(char *args)
{
	int	len;
	int	k;
	char	*value;
	
	args++;
	k = 0;
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
	return (value);
}

char	*get_name(char *args)
{
	int		len;
	char	*name;
	int		i;

	i = 0;
	len = 0;
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
	return (name);
}

void	print_name_error(char *args)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd("' : not a valid identifier\n", 2);
}

void	overwrite_env_or_new(t_env *new_env, t_env **env_list, char *name, char *value)
{
	t_env	*node;

	node = find_env_node(env_list, name);
	if (node)
	{
		node->bash_v_content = value;
		free(name);
	}
	else
		new_env = malloc(sizeof(t_env));
		new_env->bash_variable = name;
		new_env->bash_v_content = value;
		new_env->sort = 2;
		new_env->next = NULL;
		append_env_element(env_list, new_env);
}

int	get_name_arg(t_env *new_env, char *args1, t_env **env_list)
{
	char	*value;
	char	*name;
	char	*args;

	name = get_name(args1);
	args = ft_strchr(args1, '=');
	if (!check_if_valid_env(name))
	{
		print_name_error(args1);
		return (0);
	}
	if (!*(args + 1))
		value = "";
	else
		value = get_content(args);
	overwrite_env_or_new(new_env, env_list, name, value);
	return (1);
}

int	do_export(t_env **env_list, char *args)
{
	t_env	*new_env;
	int		res;

	new_env = NULL;
	if (!ft_strncmp(args, "0", 2))
	{
		print_sorted_export(env_list);
		return (1);
	}
	if (!ft_strchr(args, '='))
		return (0);
	res = get_name_arg(new_env, args, env_list);
	return (res);
}
