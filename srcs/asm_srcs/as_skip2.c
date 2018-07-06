/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_skip2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/06 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "as_errors.h"
#include <fcntl.h>

void  as_skip_to_next_param(char *line, int line_nr, int *i)
{
    int s;

    s = as_skip_space(line, i);
    if (!line[*i] && s)
        as_war1(WARNING10, line_nr, line, (*i));
    if (line[*i])
        (*i)++;
    s = as_skip_space(line, i);
    if (s > 1)
        as_war1(WARNING9, line_nr, line, (*i));
}

int  as_skip_to_params(char *line, int *i)
{
    *i = as_skip_label(line, i) + 1;
    as_skip_space(line, i);
    as_skip_command(line, i);
    as_skip_space(line, i);
    if (!line[*i])
        return (0);
    return (1);
}

int as_skip_to_sep(char *line, int *i)
{
    while (line[*i] && line[*i] != SEPARATOR_CHAR)
        (*i)++;
    return (1);
}