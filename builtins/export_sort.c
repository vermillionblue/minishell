/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:21:27 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/10 15:01:56 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

//find smallest first
//sort var: 
//sort = 2 -> unsorted
void	print_sorted_export(t_env **env_list)
{
	t_env			*temp;
	t_env			*current;
	char			*smallest;
	unsigned int	len;

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
		printf("\"");
		printf("sort var %d\n", temp->sort);
		smallest = "{{{";
		len--;
	}
	printf("declare -x ");
	printf("%s", current->bash_variable);
	printf("=");
	printf("\"");
	printf("%s", current->bash_v_content);
	printf("\"\n");
	printf("sort var %d", current->sort);
	set_sort_var(env_list);
}

t_env	*find_env_node(t_env **env_list, char *name)
{
	t_env	*temp;

	temp = *env_list;
	while(temp)
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
