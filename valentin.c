/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valentin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/06/06 19:39:41 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*				ENV List			*/

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
		ft_lstadd_back_env_element(&env_list, create_env_element(array));
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
void	ft_lstadd_back_env_element(t_env **env_list, t_env *new)
{
	t_env	*temp;

	temp = *env_list;
	if (*env_list)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		*env_list = new;
}


/*             LEXAR				*/
/* Creating the Lexar Linked List with the Arguments from the Prompt */
void	create_lexar(t_list *lexar_list, char *line)
{
	int		i;
	char	**array;

	i = 0;
	array = ft_split(line, ' ');
	if (ft_strchr(line, '"'))
		array = ft_split(line, '"');
	else if (ft_strchr(line, '\''))
		array = ft_split(line, '\'');
	while (i < size_of_array(array))
	{
		ft_lstadd_back(&lexar_list, create_element(&array[i]));
		i++;
	}
	print_list(&lexar_list);
}

/* Getting the Length of a 2D Array */
int		size_of_array(char **array)
{
	int		i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return(i);
}

/* Creating One Element to Place in a Linked List */
t_list	*create_element(char **value)
{
	t_list	*element;

	element = malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->line = *value;
	element->next = NULL;
	return (element);
}

/* Printing the Elements from a Linked List */
void	print_list(t_list **stack)
{
	t_list *temp_p;
	
	temp_p = *stack;
	if (*stack == NULL)
		printf("List is Empty\n");
	if (*stack != NULL)
	{	
		while (temp_p->next != NULL)
		{
			printf("%s", "In List: ");
			printf("%s\n", temp_p->line);
			temp_p = temp_p->next;
		}
		printf("%s", "In List: ");
		printf("%s\n", temp_p->line);
	}
}

///////////  Linked Lists Functions   /////////////




/* Getting the Lenght of the Linked List */
int	len_list(t_list **list)
{
	t_list	*temp;
	int		counter;

	temp = *list;
	counter = 0;
	if (*list != NULL)
	{
		counter = 1;
		while (temp->next != NULL)
		{
			temp = temp->next;
			counter++;
		}
	}
	return (counter);
}

/* Function to delete the entire linked list */
void	delete_list(t_list **list)
{
   /* deref **list to get the real head */
   t_list	*head;
   t_list	*next;
   
   head = *list;
   while (head != NULL) 
   {
       next = head->next;
       free(head);
       head = next;
   }
   /* deref **list to affect the real head back
      in the caller. */
   *list = NULL;
}
