/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:04:58 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/24 16:07:43 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"


int	print_env_list(t_env **env_list)
{
	t_env *temp;
	
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
