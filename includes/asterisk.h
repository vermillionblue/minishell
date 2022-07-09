/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:16:31 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/09 13:45:39 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTERISK_H
# define ASTERISK_H

# include "minishell.h"

char    *expand_wildcard(char *raw_cmd);

#endif