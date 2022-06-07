/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:04:58 by danisanc          #+#    #+#             */
/*   Updated: 2022/06/06 19:07:19 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env_list(t_env **env_list)
{
	t_env *temp;
	
	temp = *env_list;
	if (*env_list == NULL)
		perror("List is Empty\n");
	while (temp->next)
	{
		printf("%s", temp->bash_variable);
		printf("=");
		printf("%s\n", temp->bash_v_content);
		temp = temp->next;
	}
	printf("%s", temp->bash_variable);
	printf("=");
	printf("%s\n", temp->bash_v_content);
}
