/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reserve_copy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:33:00 by vangirov          #+#    #+#             */
/*   Updated: 2022/07/04 15:30:32 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*ft_concat(char *tofree, const char *nonl_buff)
{
	char	*newline;

	newline = ft_strjoin(tofree, nonl_buff);
	free(tofree);
	return (newline);
}

// void	ft_append_arg(t_list **cmd_args, char *text)
// {
// 	t_list	*new;

// 	new = ft_lstnew((void *)text);
// 	if (*cmd_args)
// 	{
// 		// printf("$$$$$$$$ TEST 2a ##########\n");
// 		ft_lstadd_back(cmd_args, new);
// 	}
// 	else
// 		*cmd_args = new;
	
// }

// int	ft_create_newargvs(t_group *group)
// {
// 	t_list	*token;
// 	int		cmd_counter;
// 	int		type;
// 	char	*text;
// 	token = *group->lexems;
// 	cmd_counter = 0;
// 	text = malloc(sizeof(char));
// 	text[0] = 0;
// 	printf("nnnnn %d\n", group->cmds->cmd_num);
// 	group->cmds->newargvs = malloc(group->cmds->cmd_num * sizeof(char **));
// 	group->cmds->cmd_args = (t_list ***)malloc(group->cmds->cmd_num * sizeof(t_list **));
// 	printf("$$$$$$$$ TEST 0 ##########\n");
// 	group->cmds->cmd_args[cmd_counter] = malloc(sizeof(t_list **)); // (t_list **)ft_calloc(1, sizeof(t_list *));
// 	if (!group->cmds->cmd_args[cmd_counter])
// 		ft_error("failed to malloc", 401);
// 	*(group->cmds->cmd_args[cmd_counter]) = malloc(sizeof(t_list *)); // Head
// 	if (!*group->cmds->cmd_args[cmd_counter])
// 		ft_error("failed to malloc", 402);
// 	printf(">>> %p\n", *group->cmds->cmd_args[cmd_counter]);
// 	while (token)
// 	{
// 		type = ft_ectracttype(token);
// 		if (type == LX_PIPE)
// 		{
// 			printf("$$$$$$$$ TEST 1 ##########\n");
// 			cmd_counter++;
// 			if (cmd_counter < group->cmds->cmd_num)
// 			{
// 				group->cmds->cmd_args[cmd_counter] = (t_list **)malloc(sizeof(t_list *)); // (t_list **)ft_calloc(1, sizeof(t_list *));
// 				*group->cmds->cmd_args[cmd_counter] = malloc(sizeof(t_list *)); // Head
// 			}
// 			// token = token->next;
// 		}
// 		else if (type == LX_SEP && ft_lstsize(*group->cmds->cmd_args[cmd_counter]))
// 		{
// 			printf("$$$$$$$$ TEST 2 ##########\n");
// 			ft_append_arg(group->cmds->cmd_args[cmd_counter], ft_ectracttext(token));
// 		}
// 		else
// 		{
// 			printf("$$$$$$$$ TEST 3 ##########\n");
// 			// printf(">>> %s$\n", ft_ectracttext(token));
// 			if (ft_lstsize(*group->cmds->cmd_args[cmd_counter]) == 0)
// 			{
// 				printf("$$$$$$$$ TEST 3a ##########\n");
// 				ft_append_arg(group->cmds->cmd_args[cmd_counter], ft_ectracttext(token));
// 			}
// 			else
// 			{
// 				printf("$$$$$$$$ TEST 3b ##########\n");
// 				text = (char *)(ft_lstlast(*group->cmds->cmd_args[cmd_counter])->content);
// 				ft_lstlast(*group->cmds->cmd_args[cmd_counter])->content = (void *)ft_concat(text, ft_ectracttext(token));
// 				printf("^^^^^^ %s\n", (char *)(ft_lstlast(*group->cmds->cmd_args[cmd_counter])->content));
// 			}
// 		}
// 		token = token->next;
// 	}
// 	// for cmds ft_lstsize
// 	// group->cmds->newargvs[cmd_counter] = malloc(sizeof(char *) * ?);
// 	return (cmd_counter);
// }

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
	int		arg_i;
	t_list	*link;
	t_list	*next;
	int		arg_num;
	int		type;
	char	*text;

	// group->cmds = malloc(sizeof(t_cmds));
	// group->cmds->cmd_num = ft_count_cmds(group->lexems);
	// if (group->cmds->cmd_num <= 0)
	// 	return(ft_error("could not parse group", -400 -(10 * group->index)));
	
	cmd_i = 0;
	while (cmd_i < group->cmds->cmd_num)
	{
		arg_i = 0;
		link = *group->cmds->cmd_args[cmd_i];
		while (link)
		{
			// type = ft_ectracttype(link);
			if (ft_ectracttype(link) != LX_SEP)
			{
				next = link->next;
				while(next && ft_ectracttype(next) != LX_SEP)
				text = ft_ectracttext(link);
				ft_concat(ft_ectracttext(next), text)
			}
			link = link->next;
		}
		// ft_dellastsep(group->cmds->cmd_args[i]);
		cmd_i++;
	}
	return (0);
}

int	ft_make_newargsvs(t_group *group)
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
		arg_num = ft_lstsize(*group->cmds->cmd_args[cmd_i]);
		group->cmds->newargvs[cmd_i] = malloc(sizeof(char *) * arg_num);
		// *group->cmds->cmd_args[i] = NULL;
		link = *group->cmds->cmd_args[cmd_i];
		while (link)
		{
			type = ft_ectracttype(link);
			group->cmds->newargvs[cmd_i][arg_i] = ft_strdup(ft_ectracttext(link));
			if (type == LX_SEP)
			{
				arg_i++;
			}
			link = link->next;
		}
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
