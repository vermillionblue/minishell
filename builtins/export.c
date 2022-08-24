/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:05:10 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 13:07:37 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

//A variable name in Bash can include letters, digits, and underscores. Its 
// name can be started with a letter and an underscore, only. Valid variable 
// names are size, tax5, and _tax20 but not 5rules.
char	*get_content(char *args)
{
	int		len;
	int		k;
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

void	overwrite_env_or_new(t_env *new_env, t_env **env_list,
char *name, char *value)
{
	t_env	*node;

	node = find_env_node(env_list, name);
	if (node)
	{
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
		append_env_element(env_list, new_env);
	}
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
		return (1);
	}
	if (!*(args + 1))
		value = "";
	else
		value = get_content(args);
	overwrite_env_or_new(new_env, env_list, name, value);
	return (0);
}

int	do_export(t_msh *msh, char *args)
{
	t_env	*new_env;
	int		res;

	new_env = NULL;
	if (!args)
	{
		sort_export(msh->env_list);
		return (0);
	}
	if (!ft_strchr(args, '='))
		return (1);
	res = get_name_arg(new_env, args, msh->env_list);
	return (res);
}
