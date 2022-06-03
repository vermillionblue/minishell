/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/06/03 14:32:30 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cmd
{
	char	cmd[1];
	char	**arg;
	struct t_cmd *next;
}				t_cmd;

typedef struct s_i_o
{
	char	*input;
	char	*output;
}				t_i_o;


int	main(int argc, char **argv, char **envp)
{
	char	cwd[256];
	char	*line;
	char	**args;
	t_list	lexar_list;

	while(1)
	{
		line = readline("minishell :D$ ");
		args = ft_split(line, ' ');
		if (!ft_strncmp(args[0], "cd", 2))
		{
			if (!args[1])
			{
				args[1] = "0";
			}
			do_cd(args[1]);
				
		}
		if (!ft_strncmp(args[0], "pwd", 3))
		{
			getcwd(cwd, sizeof(cwd));
			printf("%s\n", cwd);
		}			
	}

	(void)argc;
	(void)argv;
	(void)envp;

	return (0);
}

void	fill_linkedlst(t_cmd *cmd)
{
	char *str;

	str = "ls -l";

	cmd->arg = ft_split(str, ' ');
	//*cmd->cmd = "ls";

}