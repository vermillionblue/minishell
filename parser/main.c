#include "../includes/minishell.h"


// typedef s_msh 
// {
// 	t_buildin_ptr	buildins[7];
// 	char	reserved_words[7];
// 	char	**envp;
// 	t_list	envp_list;
// 	//list of key-value pairs that reflects the current state of envp and after it is changed the envp array has to be reassembled
// 	char	envp_f; // flag if envp has to be reassembled
// 	char	exit_t;
// 	int		status; // WIFSIGNALED(sig) waitpid(pid, &sig, 0)
// 	t_list	tokens;
// 	t_list	groups; // or command

// }	t_msh;

// #define DELIMS_FIELD		"''";
// #define DELIMS_EXT_FIELD	"\"\"";
// #define DELIMS_VAR			"$$\\ ";
// #define DELIMS_WC			"*";
// #define DELIMS_WORD			" $*'"
// #define DELIMS_AND			"&&"
// #define DELIMS_OR			"||"

void ft_fill_builtins(char **argv, t_msh msh);

// int ft_is_command(char *cmd_name, t_msh *msh);
int ft_is_builtin(char *cmd_name, t_msh *msh);

// int ft_command(char *cmd_name, char **cmd_arr, t_msh *msh);
int ft_buiLX_TYPES_NUMltin(char *cmd_name, char **cmd_arr, t_msh *msh);

/* the ptr has to point to the opening symbol */
// char	*ft_getlexem(int lx_type, char *ptr, char closing, t_list **lexems)
// {
// 	int	len;
// 	char	*start;
// 	t_list	*new;
// 	t_lexem	*lexem;

// 	len = 0;
// 	start = ptr;
// 	while (*ptr && *ptr != closing)
// 	{
// 		len++;
// 		ptr++;
// 	}
// 	lexem = ft_newlexem(lx_type, start, len);
// 	new = ft_lstnew(lexem);
// 	if (*lexems)
// 		ft_lstadd_back(lexems, new);
// 	else
// 		*lexems = new;
// 	if (*ptr == closing)
// 		ptr++;
// 	return (ptr);
// }

// char	*ft_getlexem_2(int lx_type, char *ptr, t_msh *msh)
// {
// 	int		len;
// 	char	*start;
// 	char	*closings;

// 	closings = msh->delims[lx_type] + 1;
// 	printf("%d closings:<%s>\n", lx_type, closings);
// 	len = 0;
// 	start = ptr;
// 	if (lx_type >= LX_AND && *ptr != closings[0])
// 		return (ptr);
// 	else
// 	{
// 		while (*ptr && !ft_strchr(closings, *ptr))
// 		{
// 			len++;
// 			ptr++;
// 		}
// 		ft_addlexem(msh->lexems, ft_newlexem(lx_type, ft_gettext(start, len)));
// 	}
// 	if (*ptr && (lx_type <= LX_EXT_FIELD || lx_type >= LX_AND))
// 		ptr++;
// 	return (ptr);
// }

// char	*ft_getfield(int lx_type, char *ptr, t_msh *msh)
// {
// 	int		len;
// 	char	*start;
// 	char	*closings;

// 	closings = msh->delims[lx_type] + 1;
// 	// printf("%d closings:<%s>\n", lx_type, closings);
// 	len = 0;
// 	start = ptr;
// 	while (*ptr && !ft_strchr(closings, *ptr))
// 	{
// 		len++;
// 		ptr++;
// 	}
// 	ft_addlexem(msh->lexems, ft_newlexem(lx_type, ft_gettext(start, len)));
// 	if (*ptr && lx_type <= LX_EXT_FIELD)
// 		ptr++;
// 	return (ptr);
// }

// void	ft_lexer1(char *input_line, t_msh *msh)
// {
// 	char	space = ' ';
// 	char	*ptr;
// 	// char	*start;
// 	// int		len;
// 	// char	infield;
// 	// t_list	**lexems;

// 	ft_init_delims(msh);
// 	msh->lexems = malloc(sizeof(t_list *));
// 	*msh->lexems = NULL;

// 	ptr = input_line;
// 	// printf("ptr = %s\n", ptr);
// 	while (*ptr)
// 	{
// 		int found = 0;
// 		while(*ptr && *ptr == space)
// 		{
// 			ptr++;
// 			// printf("ptr = %s\n", ptr);
// 		}
// 		int i = 0;
// 		while (!found && i < LX_NUM)
// 		{
// 			printf("delim0 %c\n", msh->delims[i][0]);
// 			if (*ptr == msh->delims[i][0])
// 			{
// 				// printf("getfield %s\n", ptr);
// 				// ptr = ft_getlexem(i, ++ptr, delims[i][1], lexems);
// 				if (msh->delims[i][1])
// 				{
// 					found++;
// 					ptr = ft_getlexem_2(i, ++ptr, msh);
// 				}
// 				else // if (*ptr != *(ptr + 1))
// 				{
// 					if (*(ptr+1) == msh->delims[i][0])
// 					{
// 						printf(">>> TEST\n");
// 						i++;
// 					}
// 					else
// 					{
// 						found++;
// 						ft_addlexem(msh->lexems, ft_newlexem(i, ""));
// 						ptr++;
// 					}
// 				}
// 				printf("gotfield %s\n", ptr);
// 			}
// 			i++;
// 		}
// 		if (!found && *ptr)
// 		{
// 			// printf("getword %s\n", ptr);
// 			ptr = ft_getlexem_2(LX_WORD, ptr, msh);
// 		}
// 	}
// 	return ;
// }

// void	ft_lexer2(char *input_line, t_msh *msh)
// {
// 	char	space = ' ';
// 	char	*ptr;
// 	// char	*start;
// 	// int		len;
// 	// char	infield;
// 	// t_list	**lexems;

// 	ft_init_delims(msh);
// 	msh->lexems = malloc(sizeof(t_list *));
// 	*msh->lexems = NULL;

// 	ptr = input_line;
// 	// printf("ptr = %s\n", ptr);
// 	while (*ptr)
// 	{
// 		int found = 0;
// 		int sep = 0;
// 		while(*ptr && *ptr == space)
// 		{
// 			ptr++;
// 			sep++;
// 			// printf("ptr = %s\n", ptr);
// 		}
// 		if (sep && ft_lstsize(*msh->lexems))
// 			ft_addlexem(msh->lexems, ft_newlexem(LX_SEP, ""));
// 		int i = 0;
// 		while (!found && i < LX_NUM)
// 		{
// 			// printf("delim0 %c\n", msh->delims[i][0]);
// 			if (*ptr == msh->delims[i][0])
// 			{
// 				// printf("getfield %s\n", ptr);
// 				// ptr = ft_getlexem(i, ++ptr, delims[i][1], lexems);
// 				if (i <=2)
// 				{
// 					found++;
// 					ptr = ft_getfield(i, ++ptr, msh);
// 				}
// 				else if (i == 3 || (i > 3 && i <= 6 && *(ptr+1) != *ptr)) // SINGLE
// 				{
// 					found++;
// 					ft_addlexem(msh->lexems, ft_newlexem(i, ""));
// 					ptr += 1;
// 				}
// 				else if (i >= 7 && *(ptr+1) == *ptr)
// 				{
// 					found++;
// 					ft_addlexem(msh->lexems, ft_newlexem(i, ""));
// 					ptr += 2;
// 				}
// 			}
// 			// if (found)
// 				// printf("gotfield %s\n", ptr);
// 			i++;
// 		}
// 		if (!found && *ptr)
// 		{
// 			// printf("getword %s\n", ptr);
// 			found++;
// 			ptr = ft_getfield(LX_WORD, ptr, msh);
// 		}
// 	}
// 	ft_dellastsep(msh);
// 	return ;
// }

void	my_printlexems(t_list **lexems)
{
	t_list *link;

	link = *lexems;
	while(link)
	{
		if(ft_strlen((*(t_lexem *)link->content).text))
			printf("[%5s]\t\t", (*(t_lexem *)link->content).text);
		else
			printf("       \t\t");
		if ((*(t_lexem *)link->content).type == LX_SEP)
			printf(" SEP \n");
		else
			printf("<%3d>\n", (*(t_lexem *)link->content).type);
		link = link->next;
	}
	printf("============\n");
}

void	my_print_arg_redir(t_group *group)
{
	for (int j = 0; j < group->cmds->cmd_num; j++)
	{
		printf("command[%d][%d]\n", group->index, j);
		my_printlexems(group->cmds->cmd_args[j]);
		printf("redirs [%d][%d]\n", group->index, j);
		my_printlexems(group->cmds->redirs[j]);
	}
}

void	my_print_newargvs(t_group *group)
{
	for (int j = 0; j < group->cmds->cmd_num; j++)
	{
		for (int k = 0; k < ft_count_args(group->cmds->cmd_args[j]); k++)
		while (*group->cmds->newargvs[j])
		{
			printf(">>> argv[%d][%d][%d] = %s\n", group->index, j, k, *group->cmds->newargvs[j]++);
		}
	}
}

void my_print_groups(t_msh *msh)
{
	if (ft_makegroups(msh) == 0)
	{
		int i = 0;

		printf("\n\n\nNUMBER OF GROUPS: %d\n", msh->group_num);
		while(i < msh->group_num)
		{
			ft_make_cmd_args(msh->groups[i]);
			msh->groups[i]->cmds->redirs = malloc(sizeof(t_list **) * msh->groups[i]->cmds->cmd_num);
			ft_loop_cmds(msh->groups[i], ft_init_redirs);
			// my_print_arg_redir(msh->groups[i]);
			printf("============================================\n");
			ft_loop_cmds(msh->groups[i], ft_format_redirs);
			ft_unite_texts(msh->groups[i]);
			ft_loop_cmds(msh->groups[i], ft_extract_redirs);
			ft_make_newargvs(msh->groups[i]);
			// printf("Group #%d (type %d, cmd_num %d):\n", i, msh->groups[i]->type, msh->groups[i]->cmds->cmd_num);
			my_print_arg_redir(msh->groups[i]);
			my_print_newargvs(msh->groups[i]);
			printf("============================================\n");
			i++;
		}
	}
}

/* Order of calling commands: 
	- make cmd_args > list
	- expand $vars
	- unites texts
	- parse of redirs
	*/
int main(int argc, char const *argv[])
{
	char	*line;
	t_msh	msh;
	// t_list	**lexems;

	if (argc > 1)
	{
		printf("%s: too many arguments\n", argv[0]); //////////////////
		return (1);
	}
	ft_init_delims(&msh);
	while(1)
	{
		line = readline("myprompt$> ");
		ft_lexer(line, &msh);
		if (!ft_count_groups(*&msh.lexems))
			continue ;
		add_history(line);
		my_printlexems(msh.lexems);
		// my_print_groups(&msh);
		// printf(">>>>>> TEST\n");
		// if (ft_is_builtin(line, &msh))
		// 	ft_builtin(line, NULL, &msh);
		// else
		// 	printf("built-in-command does not exist (yet?)...");
	}
	free(line);
	// init
	// 	all ptrs, keywords
	// 	envp, envp_list
	// while (!exit_f)
	// {
	// 	ft_readline != 0 // readline + renew history
	// 	lexer // tokens
	// 	parser
	// 	executor
	// }
	// destructor
}

// int main(int argc, char const *argv[])
// {
	
// }

//       12  "3   4" '5   6'    <<  >>  < > || | &&&          
//    00 11$22 33 | 44 55 | 66 || 77 88 && 99 00 11 | 22   