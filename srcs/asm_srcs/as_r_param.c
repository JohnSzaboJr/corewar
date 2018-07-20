/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_r_param.c                                       :+:      :+:    :+:   */
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
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int as_check_r_chars(char *line, int i, int j, t_list_error **error)
{
    char    c;
    int     k;

    k = i;
    while (line[i] != 'r' && !ft_isspace(line[i]))
        i--;
    if (k != i && line[i] != 'r')
    {
        if (!as_add_error(error, ERROR20, line, k))
            return (0);
        return (-1);
    }
    i = k;
    c = line[i];
    line[i] = '\0';
    if (line[j + 1] == '-' || ft_hasnondigits(line + j + 1))
    {
        line[i] = c;
        if (!as_add_error(error, ERROR11, line, j + 1))
            return (0);
        return (-1);
    }
    line[i] = c;
    return (1);
}

int as_check_r_length(char *line, int i, int j, t_list_error **error)
{
    char c;

    c = line[i];
    line[i] = '\0';
    if (ft_atoi(line + j + 1) > REG_NUMBER || ft_strlen(line + j + 1) > (size_t)ft_numlen(REG_NUMBER))
    {
        line[i] = c;
        if (!as_add_note_reg(error, ERROR13, line, j + 2))
            return (0);
        return (-1);
    }
    line[i] = c;
    return (1);
}

int as_check_r_zero(char *line, int i, int j, t_list_error **error)
{
    char c;

    c = line[i];
    line[i] = '\0';
    if (!ft_atoi(line + j + 1))
    {
        line[i] = c;
        if (!as_add_note_reg(error, ERROR14, line, j + 2))
            return (0);
        return (-1);
    }
    line[i] = c;
    return (1);
}
