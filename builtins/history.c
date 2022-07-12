/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 21:35:15 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/11 21:54:42 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	fd_add_history(char *line, t_list **history)
(
	t_list *node;

	node = (t_list *)malloc(sizeof(t_list));
	ft_lstadd_back(history, node);
)