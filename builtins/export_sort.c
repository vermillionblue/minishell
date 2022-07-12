/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:21:27 by danisanc          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/10 21:05:07 by danisanc         ###   ########.fr       */
=======
/*   Updated: 2022/07/11 17:13:10 by danisanc         ###   ########.fr       */
>>>>>>> dani
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

//sort = 2 -> unsorted
char	*find_smallest(t_env *current, char *smallest)
{
	while (current)
	{	
		if ((ft_strncmp(current->bash_variable, smallest,
					ft_strlen(current->bash_variable)) < 0)
			&& current->sort == 2)
			smallest = current->bash_variable;
		if (current->next)
			current = current->next;
		else
			break ;
	}
	return (smallest);
}

void	print_sorted_export(t_env *temp)
{
	printf("declare -x ");
	printf("%s", temp->bash_variable);
	printf("=");
	printf("\"");
	printf("%s", temp->bash_v_content);
	printf("\"\n");
}

void	sort_export(t_env **env_list)
{
	t_env			*temp;
	t_env			*current;
	char			*smallest;
	unsigned int	len;

	len = env_list_size(env_list);
	printf("list len %d\n", len);
	current = *env_list;
	smallest = current->bash_variable;
	if (*env_list == NULL)
		perror("List is Empty\n");
<<<<<<< HEAD
	while(len > 0)
	{
		current = *env_list;
		while (current)
		{	
			if ((ft_strncmp(current->bash_variable, smallest, ft_strlen(current->bash_variable)) < 0) && current->sort == 2)
				smallest = current->bash_variable;
			if (current->next)
				current = current->next;
			else
				break ;
		}
		len--;
		temp = find_env_node(env_list, smallest);
		temp->sort = 1;
		printf("declare -x ");
		printf("%s", temp->bash_variable);
		printf("=");
		printf("\"");
		printf("%s", temp->bash_v_content);
		printf("\"\n");
=======
	while (len > 0)
	{
		current = *env_list;
		smallest = find_smallest(current, smallest);
		len--;
		temp = find_env_node(env_list, smallest);
		temp->sort = 1;
		print_sorted_export(temp);
>>>>>>> dani
		smallest = "{";
	}
	set_sort_var(env_list);
}

t_env	*find_env_node(t_env **env_list, char *name)
{
	t_env	*temp;

	temp = *env_list;
	while (temp)
	{
		if (!ft_strncmp(temp->bash_variable, name,
				ft_strlen(temp->bash_variable) + 1))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	set_sort_var(t_env **env_list)
{
	t_env	*temp;

	temp = *env_list;
	while (temp->next)
	{
		temp->sort = 2;
		temp = temp->next;
	}
	temp->sort = 2;
}
