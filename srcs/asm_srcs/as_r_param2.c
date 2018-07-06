/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_r_param2.c                                      :+:      :+:    :+:   */
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

static int as_check_r(char *line, int *i, int j, int line_nr)
{
    as_skip_rev_space(line, i);
    if (!as_check_r_chars(line, *i, j, line_nr) || 
    !as_check_r_length(line, *i, j, line_nr) ||
    !as_check_r_zero(line, *i, j, line_nr))
        return (0);
    return (1);
}

static int  as_check_errors_r(int line_nr, char *line, int *i, t_list_byte **code)
{
    int j;

    j = as_j(0, 0);
    if (!line[j + 1] || ft_isspace(line[j + 1]) || line[j + 1] == SEPARATOR_CHAR)
        as_err1(ERROR12, line_nr, line, j + 2);
    else if (line[j + 1])
    {
        if (!as_check_r(line, i, j, line_nr))
            return (0);
        else if (!as_check_r_params(as_get_pos((*code)->byte, 0), as_k(0)))
        {
            as_err1(ERROR15, line_nr, line, j + 1);
            as_err_note3(line_nr, j + 1, as_get_pos((*code)->byte, 0), as_k(0));
            return (0);
        }
    }
    return (1);
}

int as_reg(char *line, int line_nr, int *i, t_list_byte **code)
{
    if ((line[as_j(0, 0)] == 'r') &&
    as_check_errors_r(line_nr, line, i, code))
        return (1);
    return (0);
}

int as_s_reg(t_list_byte **code, t_list_byte **encoding, char *line)
{
    if (as_check_r_params2(as_get_pos((*code)->byte, 0), as_k(0), encoding) &&
    !(as_add_byte(code, (unsigned char)ft_atoi(line + as_j(0, 0) + 1))))
        return (0);
    return (1);
}