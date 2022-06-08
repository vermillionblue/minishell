/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:05:10 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/07 16:24:16 by danisanc         ###   ########.fr       */
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
t_env	*find_env_node(t_env **env_list, char *name)
{
	t_env	*temp;

	temp = *env_list;
	while(temp->next)
	{
		if (!ft_strncmp(temp->bash_variable, name, ft_strlen(temp->bash_variable) + 1))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	set_sort_var(t_env **env_list)
{
	t_env	*temp;

	temp = *env_list;
	while(temp->next)
	{
		temp->sort = 2;
		temp = temp->next;
	}
	temp->sort = 2;
}
//find smallest first
//sort var: 
//sort = 2 -> unsorted
void	print_sorted_export(t_env **env_list)
{
	t_env			*temp;
	t_env			*current;
	char			*smallest;
	int				i;
	unsigned int	len;

	i = 0;
	len = env_list_size(env_list);
	current = *env_list;
	smallest = current->bash_variable;
	if (*env_list == NULL)
		perror("List is Empty\n");
	while(len > 1)
	{
		current = *env_list;
		while (current->next)
		{	
			if ((ft_strncmp(current->bash_variable, smallest, ft_strlen(current->bash_variable)) < 0) && current->sort == 2)
				smallest = current->bash_variable;
			current = current->next;
		}
		temp = find_env_node(env_list, smallest);
		temp->sort = 1;
		printf("declare -x ");
		printf("%s", temp->bash_variable);
		printf("=");
		printf("\"");
		printf("%s", temp->bash_v_content);
		printf("\"\n");
		smallest = "{{{";
		len--;
	}
	set_sort_var(env_list);
}

int	do_export(t_env **env_list, char *args)
{
	t_env	*new_env;
	char	**temp;

	//check if name is already in env
	//fix vars with double = : miau=miau=miau
	if (!ft_strncmp(args, "0", 1))
	{
		print_sorted_export(env_list);
		return (1);
	}
	if (!ft_strchr(args, '='))
		return (0);
	if (check_args(args))
	{
		if (args[ft_strlen(args) - 1] == '=')
		{
			args[ft_strlen(args) - 1] = '\0';
			temp[0] = ft_strdup(args);
			temp[1] = "";
		}
		else
			temp = ft_split(args, '=');
		if (!find_env_node(env_list, temp[0]))
		{
			printf("%stemp0\n", temp[0]);
			new_env = malloc(sizeof(t_env));
			new_env->bash_variable = ft_strdup(temp[0]);
			new_env->bash_v_content = ft_strdup(temp[1]);
			// printf("%s\n", new_env->bash_variable);
			// printf("%s\n", new_env->bash_v_content);
			new_env->sort = 2;
			new_env->next = NULL;
			ft_lstadd_back_env_element(env_list, new_env);
		}
		else
		{
			//working when there are two envs with the same name 
			new_env = find_env_node(env_list, temp[0]);
			new_env->bash_v_content = ft_strdup(temp[1]);
			printf("%s\n", new_env->bash_v_content);
		}
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