/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/06/22 11:44:28 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_is_builtin(char *str)
// {
	
// }

int	main(int argc, char **argv, char **envp)
{
	char	cwd[256];
	char	*line;
	char	**args;
	t_env	*env_list;

	printf("%s name\n", xstr(cddd));
	env_list = create_env_list(envp);
	while(1)
	{
		line = readline("\001\033[0;35mminishell 😁$\033[0;37m\002 ");
		args = ft_split(line, ' ');
		if (!ft_strncmp(args[0], "cd", 2))
		{
			if (!args[1])
				args[1] = "0";
			do_cd(args[1]);
		}
		else if (!ft_strncmp(args[0], "pwd", 3))
			do_cwd();
		else if (!ft_strncmp(args[0], "env", 3))
			print_env_list(&env_list);
		else if (!ft_strncmp(args[0], "export", 6))
		{
			if (!args[1])
				args[1] = "0";
			do_export(&env_list, args[1]);
		}
		else if (!ft_strncmp(args[0], "unset", 5))
			do_unset(&env_list, args[1]);		
		else if (!ft_strncmp(args[0], "exit", 4))
			do_exit();
		else if (!ft_strncmp(args[0], "exec", 4))
		{
			printf("trigger\n");
			start_exec(envp);	
		}
	}
	return (0);
}
