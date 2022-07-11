/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:04:58 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/11 17:14:17 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

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

int	print_env_list(t_env **env_list)
{
	t_env	*temp;

	temp = *env_list;
	if (*env_list == NULL)
	{
		perror("List is Empty\n");
		return (0);
	}
	while (temp)
	{
		printf("%s", temp->bash_variable);
		printf("=");
		printf("%s\n", temp->bash_v_content);
		temp = temp->next;
	}
	return (1);
}
