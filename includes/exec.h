/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:18:43 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/06 00:28:52 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "builtins.h"


//exec
int	exec_group(t_group *group, char **env, t_msh *msh);
void	prep_groups(char **env, t_msh *msh);
void	ft_exec();

#endif