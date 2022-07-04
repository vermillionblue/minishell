/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:33:00 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/04 15:30:40 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_error(char *error_text, int error_num)
{
	ft_fdprintf(2, "minishell: %s (%d)\n", error_text, -error_num);
	return (error_num);
}

/* if the first token is AND or OR print error */
int	ft_count_groups(t_list **lexems)
{
	int	counter;
	int type;

	t_list *link;
	if (!*lexems)
		return (0);
	counter = 1;
	link = *lexems;
	type = ft_ectracttype(link);
	if (type == LX_AND || type == LX_OR)
		return(ft_error("syntax error: || or && as the first token", -301));
	type = ft_ectracttype(ft_lstlast(link));
	if (type == LX_AND || type == LX_OR)
		return(ft_error("syntax error: || or && as the last token", -399));
	while (link)
	{
		type = ft_ectracttype(link);
		if (type == LX_AND || type == LX_OR)
			counter++;
		link = link->next;
	}
	return (counter);
}

/* if the first token is PIPE print error */
int	ft_count_cmds(t_list **lexems)
{
	int	counter;
	int type;

	t_list *link;
	// if (ft_lstsize(*lexems) == 1)
	// 	return (0);
	counter = 1;
	link = *lexems;
	type = ft_ectracttype(link);
	if (type == LX_PIPE)
		return(ft_error("syntax error: | the first token of a group", -401));
	type = ft_ectracttype(ft_lstlast(link));
	if (type == LX_PIPE)
		return(ft_error("syntax error: | the last token of a group", -499));
	while (link)
	{
		type = ft_ectracttype(link);
		if (type == LX_PIPE)
			counter++;
		link = link->next;
		
	}
	
	return (counter);
}

int	ft_count_args(t_list **cmd_args)
{
	int	counter;
	int type;

	t_list *link;
	// if (ft_lstsize(*lexems) == 1)
	// 	return (0);
	counter = 0;
	link = *cmd_args;
	type = ft_ectracttype(link);
	// if (type == LX_PIPE)
	// 	return(ft_error("syntax error: | the first token of a group", -401));
	// type = ft_ectracttype(ft_lstlast(link));
	// if (type == LX_PIPE)
	// 	return(ft_error("syntax error: | the last token of a group", -499));
	while (link)
	{
		type = ft_ectracttype(link);
		if (type != LX_SEP && type != LX_AND && type != LX_OR)
			counter++;
		link = link->next;
		
	}
	
	return (counter);
}

char	*ft_concat(char *line, char *nonl_buff)
{
	char	*newline;

	newline = ft_strjoin(line, nonl_buff);
	free(line);
	return (newline);
}

char	*ft_strjoinfree(char *tofree1, char *tofree2)
{
	char	*newline;

	newline = ft_strjoin(tofree1, tofree2);
	free(tofree1);
	free(tofree2);
	return (newline);
}

void	ft_append_arg(t_list **cmd_args, char *text)
{
	t_list	*new;

	new = ft_lstnew((void *)text);
	if (*cmd_args)
	{
		// printf("$$$$$$$$ TEST 2a ##########\n");
		ft_lstadd_back(cmd_args, new);
	}
	else
		*cmd_args = new;
	
}

int	ft_make_cmd_args(t_group *group)
{
	int		i;
	t_list	*link;
	int		type;
	char	*text;

	group->cmds = malloc(sizeof(t_cmds));
	group->cmds->cmd_num = ft_count_cmds(group->lexems);
	if (group->cmds->cmd_num <= 0)
		return(ft_error("could not parse group", -400 -(10 * group->index)));
	
	group->cmds->cmd_args = malloc(sizeof(t_list **) * group->cmds->cmd_num);
	i = 0;
	link = *group->lexems;
	while (i < group->cmds->cmd_num)
	{
		group->cmds->cmd_args[i] = malloc(sizeof(t_list *));
		*group->cmds->cmd_args[i] = NULL;
		while (link)
		{
			type = ft_ectracttype(link);
			if (type == LX_PIPE && *group->cmds->cmd_args[i])
			{
				link = link->next;
				break ;
			}
			if (!(type == LX_SEP && !*group->cmds->cmd_args[i]))
			{
				text = ft_ectracttext(link);
				ft_addlexem(group->cmds->cmd_args[i], ft_newlexem(type, text));
			}
			link = link->next;
		}
		ft_dellastsep(group->cmds->cmd_args[i]);
		i++;
	}
	return (0);
}

int	ft_unite_texts(t_group *group)
{
	int		cmd_i;
	t_list	*link;
	t_list	*next;

	cmd_i = 0;
	while (cmd_i < group->cmds->cmd_num)
	{
		link = *group->cmds->cmd_args[cmd_i];
		while (link)
		{
			// type = ft_ectracttype(link);
			if (ft_ectracttype(link) != LX_SEP)
			{
				
				next = link->next;
				while(next && ft_ectracttype(next) != LX_SEP)
				{
					// text = ft_ectracttext(link);
					((t_lexem *)(link->content))->text = \
						// ft_concat(ft_ectracttext(link), ft_ectracttext(next));
						ft_strjoin(ft_ectracttext(link), ft_ectracttext(next));
					// free(text);
					// printf("TEST\n");
					link->next = next->next;
					free(next->content);
					free(next);
					next = link->next;
					// printf(">>> TEST >>>\n");
				}
			}
			// printf(">>> TEST >>>\n");
			link = link->next;
		}
		// ft_dellastsep(group->cmds->cmd_args[i]);
		cmd_i++;
	}
	return (0);
}

int	ft_make_newargvs(t_group *group)
{
	int		cmd_i;
	int		arg_i;
	t_list	*link;
	int		arg_num;
	int		type;
	// char	*text;

	// group->cmds = malloc(sizeof(t_cmds));
	// group->cmds->cmd_num = ft_count_cmds(group->lexems);
	// if (group->cmds->cmd_num <= 0)
	// 	return(ft_error("could not parse group", -400 -(10 * group->index)));
	
	group->cmds->newargvs = malloc(sizeof(char **) * group->cmds->cmd_num);
	cmd_i = 0;
	link = *group->lexems;
	while (cmd_i < group->cmds->cmd_num)
	{
		arg_i = 0;
		arg_num = ft_count_args(group->cmds->cmd_args[cmd_i]);
		group->cmds->newargvs[cmd_i] = malloc(sizeof(char *) * arg_num + 1);
		// *group->cmds->cmd_args[i] = NULL;
		link = *group->cmds->cmd_args[cmd_i];
		while (link)
		{
			type = ft_ectracttype(link);
			if (type != LX_SEP && type != LX_AND && type != LX_OR)
			{
				group->cmds->newargvs[cmd_i][arg_i] = ft_strdup(ft_ectracttext(link));
				// printf("------- argv[%d][%d][%d] = %s\n", group->index, cmd_i, arg_i, group->cmds->newargvs[cmd_i][arg_i]);
				arg_i++;
			}
			link = link->next;
		}
		group->cmds->newargvs[cmd_i][arg_i] = 0;
		// ft_dellastsep(group->cmds->cmd_args[i]);
		cmd_i++;
	}
	return (0);
}

// int	ft_create_cmds(t_msh *msh)
// {
// 	int i;
// 	// t_list	*link;

// 	i = 0;
// 	// link = *msh->lexems;
// 	while (i < msh->group_num)
// 	{
// 		msh->groups[i]->cmds = ft_calloc(1, sizeof(t_cmds *));
// 		msh->groups[i]->cmds->cmd_num = ft_count_cmds(msh->groups[i]->lexems);
		
// 		printf(">>>> cmd n = %d\n", msh->groups[i]->cmds->cmd_num);
// 		if (msh->groups[i]->cmds->cmd_num < 0)
// 			return(ft_error("could not parse group #%d", -400));
		
// 		msh->groups[i]->cmds->pipe_num = msh->groups[i]->cmds->cmd_num - 1;

// 		// HERE EXPANTION OF VARS
// 		// HERE EXPANTION OF WC
// 		// msh->groups[i]->cmds = malloc(sizeof(t_cmds *));
// 		// printf(">>>>>>> %d\n", ft_create_newargvs(msh->groups[i]));
// 		i++;
// 	}
// 	return (0);
// }


int	ft_makegroups(t_msh *msh)
{
	// int		gr_num;
	int		i;
	t_list	*link;
	int		type;
	char	*text;

	msh->group_num = ft_count_groups(msh->lexems);
	if (msh->group_num <= 0)
		return(ft_error("could not parse", -300));
	
	msh->groups = malloc(sizeof(t_group *) * msh->group_num);
	i = 0;
	link = *msh->lexems;
	while (i < msh->group_num)
	{
		msh->groups[i] = malloc(sizeof(t_group));
		msh->groups[i]->index = i;
		msh->groups[i]->lexems = malloc(sizeof(t_list *));
		*msh->groups[i]->lexems = NULL;
		if (i == 0)
			msh->groups[i]->type = -1;
		else
			msh->groups[i]->type = ft_ectracttype(link);
		while (link)
		{
			type = ft_ectracttype(link);
			if ((type == LX_AND || type == LX_OR) && *msh->groups[i]->lexems)
				break ;
			text = ft_ectracttext(link);
			ft_addlexem(msh->groups[i]->lexems, ft_newlexem(type, text));
			link = link->next;
		}
		ft_dellastsep(msh->groups[i]->lexems);

		// /////////////////////////////////////////////////////////////
		// msh->groups[i]->cmds = malloc(sizeof(t_cmds *));
		// msh->groups[i]->cmds->cmd_num = ft_count_cmds(msh->groups[i]->lexems);
		// if (msh->groups[i]->cmds->cmd_num < 0)
		// 	return(ft_error("could not parse group #%d", -400));
		i++;
	}
	return (0);
}


void	ft_parser(t_msh *msh);
        //   ls -la || echo | gekee && make | re       



// int	ft_create_cmds(t_msh *msh)
// {
// 	int i;
// 	t_list	*link;

// 	i = 0;
// 	link = *msh->lexems;
// 	while (i < msh->group_num)
// 	{
// 		msh->groups[i]->cmds = malloc(sizeof(t_cmds *));
// 		msh->groups[i]->cmds->cmd_num = ft_count_cmds(msh->groups[i]->lexems);
// 		if (msh->groups[i]->cmds->cmd_num < 0)
// 			return(ft_error("could not parse group #%d", -400));
// 		msh->groups[i]->cmds->pipe_num = msh->groups[i]->cmds->cmd_num - 1;

// 		// HERE EXPANTION OF VARS
// 		// HERE EXPANTION OF WC
		
// 		// msh->groups[i]->cmds = malloc(sizeof(t_cmds *));
		
// 		i++;
// 	}
// 	return (0);
// }

int	ft_is_redir(int type)
{
	if (type == LX_REDIR_OUT || type == LX_REDIR_IN ||
		type == LX_REDIR_APPEND || type == LX_REDIR_INSRC)
		return (type);
	else
		return (-1);
}


/* Has to be called after uniting texts */
/* int	ft_parse_for_redirections(t_group *group)
{
	int		cmd_i;
	t_list	*link;
	t_list	*next;

	group->cmds->redirs = malloc(sizeof(t_list **));
	*group->cmds->redirs
	
	cmd_i = 0;
	while (cmd_i < group->cmds->cmd_num)
	{
		link = *group->cmds->cmd_args[cmd_i];
		while (link)
		{
			if (ft_is_redir_type(ft_ectracttype(link)))   //        <<<-----------------
			{
				
				next = link->next;
				while(next && ft_ectracttype(next) != LX_SEP)
				{
					// text = ft_ectracttext(link);
					((t_lexem *)(link->content))->text = \
						ft_concat(ft_ectracttext(link), ft_ectracttext(next));
					// free(text);
					printf("TEST\n");
					link->next = next->next;
					free(next->content);
					free(next);
					next = link->next;
					// printf(">>> TEST >>>\n");
				}
			}
			// printf(">>> TEST >>>\n");
			link = link->next;
		}
		// ft_dellastsep(group->cmds->cmd_args[i]);
		cmd_i++;
	}
	return (0);
}
*/

void	ft_free_lexem(t_list *link)
{
	if (ft_ectracttype(link) <= LX_VAR)
		free(ft_ectracttext(link));
	free(link->content);
	free(link);
}

/*	The function checks if there is anything to redirect after redirection symbol
	and removes all separators between the symbol and the redirection file */
void	ft_format_redirs(t_group *group, int cmd_i)
{
	t_list	*link;
	t_list	*next;
	int		type;

	link = *group->cmds->cmd_args[cmd_i];
	while (link)
	{
		type = ft_ectracttype(link);
		if (ft_is_redir(type) > 0)
		{
			next = link->next;
			if (!next)
			{
				ft_error("No argument after redirection operator [Gr %d, Cmd %d]", \
					-(700 + 10 * group->index + cmd_i));
				return ;
			}
			else if (ft_ectracttype(next) == LX_SEP)
			{
				printf("deleteing SEP\n");
				link->next = next->next;
				printf("TEST <\n");
				ft_free_lexem(next);
			}
		}
		link = link->next;
	}
	// return (0);
}

int	ft_push_lesem(t_list *dest, t_list **head, t_list *link)
{
	t_list *src;

	if (dest && link)
		dest->next = link->next;
	if (!*head)
	{
		*head = link;
		link->next = NULL;
	}
	else
	{
		src = ft_lstlast(*head);
		
		link->next = src->next;
		src->next = link;
	}
	return (0);
}

// int ft_pickup_redirs(t_group *group, int	cmd_i)
// {
// 	t_list	*link;
// 	t_list	*temp;

// 	link = *group->cmds->cmd_args[cmd_i];
// 	while (link)
// 	{
// 		if (link->next && ft_is_redir(ft_ectracttype(link->next)) > 0)
// 		{
// 			ft_push_lesem(link, group->cmds->redirs[cmd_i], link->next);
// 			if (link->next)
// 				ft_push_lesem(link, group->cmds->redirs[cmd_i], link->next);
// 			if (link->next && ft_ectracttype(link) == LX_SEP && ft_ectracttype(link->next) == LX_SEP)
// 			{
// 				temp = link->next;
// 				link->next = link->next->next;
// 				printf("TEST ddd\n");
// 				free(temp);
// 				continue;
// 			}
// 		}
// 		link = link->next;
// 	}
// 	return (0);
// }

/* Pushes the SEP and the filename to the redir list*/
// t_list	*ft_push_redir(t_list **headfrom, t_list *target, t_list **headto)
// {
// 	t_list	*next;
// 	t_list	*nextnext;

// 	next = target->next;
// 	ft_lstpush_behind_link(headfrom, target, headto, NULL);
// 	if (next)
// 	{
// 		nextnext = next->next;
// 		ft_lstpush_behind_link(headfrom, next, headto, NULL);
// 	}
// 	return (nextnext);
// }

void	ft_extract_redirs(t_group *group, int cmd_i)
{
	t_list	*link;
	t_list	*temp;

	link = *group->cmds->cmd_args[cmd_i];
	// printf(">>test: %d\n", ft_ectracttype(link));
	while (link)
	{
		// printf("Ed redir\n");
		if (ft_is_redir(ft_ectracttype(link)) > 0)
		{
			temp = link->next;
			ft_lst_detach_from(group->cmds->cmd_args[cmd_i], link);
			ft_lstadd_back(group->cmds->redirs[cmd_i], link);
			link = temp;
			continue;
		}
		link = link->next;
	}
	ft_dellastsep(group->cmds->cmd_args[cmd_i]);
}


// /* Has to be called after uniting texts */
int	ft_make_redirs(t_group *group)
{
	int		i;
	// t_list	*link;
	// t_list	*next;
	// int		type;

	group->cmds->redirs = malloc(sizeof(t_list **) * group->cmds->cmd_num);
	i = 0;
	
	while (i < group->cmds->cmd_num)
	{
		// link = *group->cmds->cmd_args[i];
		group->cmds->redirs[i] = malloc(sizeof(t_list *));
		*group->cmds->redirs[i] = NULL;
		printf(">>test: %p\n", *group->cmds->cmd_args[i]);
		ft_format_redirs(group, i);
		// ft_pickup_redirs(group, i);
		ft_extract_redirs(group, i);
		i++;
	}
	return (0);
}

void	ft_init_redirs(t_group *group, int cmd_i)
{
		group->cmds->redirs[cmd_i] = malloc(sizeof(t_list *));
		*group->cmds->redirs[cmd_i] = NULL;
}

void	ft_loop_cmds(t_group *group, void (*opearation)(t_group *, int i))
{
	int	cmd_i;

	cmd_i = 0;
	while(cmd_i < group->cmds->cmd_num)
	{
		opearation(group, cmd_i);
		cmd_i++;
	}
}
