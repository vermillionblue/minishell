/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:58:38 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/24 13:06:55 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**list_to_arr(t_env **env_list)
{
	char			**new_arr;
	t_env			*temp;
	char			*holder;
	int				i;

	i = 0;
	new_arr = (char **)ft_calloc((env_list_size(env_list)
				+ 1), sizeof(char *) + 1);
	temp = *env_list;
	while (temp)
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

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		if (envp[i][ft_strlen(envp[i]) - 1] == '=')
		{
			array = malloc(sizeof(char *) * 2);
			array[0] = malloc(ft_strlen(envp[i]));
			ft_strlcpy(array[0], envp[i], ft_strlen(envp[i]));
			array[1] = ft_strdup("");
		}
		else
			array = ft_split(envp[i], '=');
		append_env_element(&env_list, create_env_element(array));
		i++;
	}
	return (env_list);
}

t_env	*create_env_element(char **value)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (!element)
		return (NULL);
	element->bash_variable = ft_strdup(value[0]);
	element->bash_v_content = ft_strdup(value[1]);
	element->sort = 2;
	element->next = NULL;
	free_double(value);
	return (element);
}

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
