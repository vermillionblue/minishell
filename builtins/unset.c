/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:36:41 by danisanc          #+#    #+#             */
/*   Updated: 2022/08/23 20:15:11 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	check_unset_name(char *name)
{
	int	i;

	i = 1;
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);
	if (ft_strchr(name, '='))
		return (0);
	while (name[i])
	{
		if (name[i] != '_' && !(ft_isalnum(name[i])))
			return (0);
		i++;
	}
	return (1);
}

void	print_unset_error_or_nothing(char *name, t_env **env_list, int *res)
{
	if (!name)
		*res = 0;
	if (!check_unset_name(name))
	{
		ft_putstr_fd("unset: '", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("' : not a valid identifier\n", 2);
		*res = 1;
	}
	if (*env_list == NULL)
	{
		perror("List is Empty\n");
		*res = 1;
	}
}

int	do_unset(t_msh *msh, char *name)
{
	t_env	*temp;
	int		res;
	t_env	**env_list;

	env_list = msh->env_list;
	temp = *env_list;
	res = 0;
	print_unset_error_or_nothing(name, env_list, &res);
	if (!ft_strncmp(temp->bash_variable, name, ft_strlen(name)))
	{
		*env_list = temp->next;
		return (0);
	}
	while (temp->next)
	{
		if (!ft_strncmp(temp->next->bash_variable, name, ft_strlen(name) + 1))
		{
			temp->next = temp->next->next;
			return (0);
		}
		temp = temp->next;
	}
	if (msh->env)
		free_double(msh->env);
	msh->env = list_to_arr(msh->env_list);
	return (res);
}
