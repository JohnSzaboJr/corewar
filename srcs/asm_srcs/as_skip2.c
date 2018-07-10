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

int  as_skip_to_next_param(char *line, t_list_error **error, int *i)
{
    int s;

    s = as_skip_space(line, i);
    if (!line[*i] && s && !as_add_warning(error, WARNING10, line, (*i)))
        return (0);
    if (line[*i])
        (*i)++;
    s = as_skip_space(line, i);
    if (s > 1 && !as_add_warning(error, WARNING9, line, (*i)))
        return (0);
    return (1);
}

int  as_skip_to_params(char *line, int *i)
{
    *i = as_skip_label(line, i);
    if (line[*i] == LABEL_CHAR)
        (*i)++;
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