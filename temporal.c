/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 20:02:59 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/27 18:28:10 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **list_to_arr(t_env **env_list)
{
	char			**new_arr;
	t_env			*temp;
	char			*holder;
	int				i;
	
	i = 0;
	new_arr = (char **)malloc(sizeof(char *) * (env_list_size(env_list) + 1));
	temp = *env_list;
	//printf("%s first var\n", temp->bash_variable);
	while(temp)
	{
		holder = ft_strjoin(temp->bash_variable, "=");
		new_arr[i] = ft_strjoin(holder, temp->bash_v_content);
		free(holder);
		i++;
		temp = temp->next;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

t_env	*create_env_list(char	**envp)
{
	t_env	*env_list;
	char	**array;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	env_list = NULL;
	while (envp[i])
	{
		if (envp[i][ft_strlen(envp[i]) - 1] == '=')
		{
			array[0] = ft_strdup(envp[i]);
			array[1] = "";
		}
		else
			array = ft_split(envp[i], '=');
		append_env_element(&env_list, create_env_element(array));
		i++;
	}
	return (env_list);
}
/* Creating One Element with Two Variables to Place in a Linked List */
t_env	*create_env_element(char **value)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (!element)
		return (NULL);
	element->bash_variable = value[0];
	element->bash_v_content = value[1];
	element->sort = 2;
	element->next = NULL;
	return (element);
}
/* Adding Elements to the back of the ENV List (Modified ft_lstadd_back) */
void	append_env_element(t_env **env_list, t_env *new)
{
	t_env	*temp;

	temp = *env_list;
	if (*env_list)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*env_list = new;
}
