/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/06/24 13:33:38 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env_list;

	(void) argc;
	(void) argv;
	env_list = create_env_list(envp);
	while(1)
	{
		//env_list = create_env_list(envp);
		line = readline("\033[0;35mminishell 🦄$\033[0;37m");
		envp = list_to_arr(&env_list);
		ft_redirect(line, env_list);
	}
	return (0);
}
