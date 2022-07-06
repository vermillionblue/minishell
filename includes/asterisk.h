/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:16:31 by danisanc          #+#    #+#             */
/*   Updated: 2022/07/06 12:23:02 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTERISK_H
# define ASTERISK_H

# include "minishell.h"

char    *expand_wildcard(char *raw_cmd);
void    print_regex_error(char *cmd, char *regex);


#endif