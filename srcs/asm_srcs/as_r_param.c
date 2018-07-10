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
    if (ft_atoi(line + j + 1) > 255 || ft_strlen(line + j + 1) > 3)
    {
        line[i] = c;
        if (!as_add_note(error, NOTE1, line, j + 2))
            return (0);
        if (!as_add_error(error, ERROR13, line, j + 2))
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
        if (!as_add_note(error, NOTE1, line, j + 2))
            return (0);
        if (!as_add_error(error, ERROR14, line, j + 2))
            return (0);
        return (-1);
    }
    line[i] = c;
    return (1);
}

int as_check_r_params(int co, int k)
{
    if (k <= op_tab[co].param_count && op_tab[co].param_type[k - 1] != T_REG &&
        op_tab[co].param_type[k - 1] != T_REG + T_DIR &&
        op_tab[co].param_type[k - 1] != T_REG + T_DIR + T_IND)
        return (0);
    return (1);
}

int as_add_r_encoding(int co, int k, t_list_byte **encoding)
{
    if (k <= op_tab[co].param_count && *encoding)
    {
        if (k == 1)
            (*encoding)->byte = (unsigned char)64;
        if (k == 2)
            (*encoding)->byte = (*encoding)->byte + (unsigned char)16;
        if (k == 3)
            (*encoding)->byte = (*encoding)->byte + (unsigned char)4;
    }
    return (1);
}
