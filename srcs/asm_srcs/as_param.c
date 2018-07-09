/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_param.c                                         :+:      :+:    :+:   */
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

int    as_check_valid_params(t_list_error **error, char *line)
{
    if (line[as_j(0, 0)] != 'r' && line[as_j(0, 0)] != DIRECT_CHAR &&
    !(ft_isdigit(line[as_j(0, 0)]) || line[as_j(0, 0)] == '-'))
    {
        if (!as_add_error(error, ERROR11, line, as_j(0, 0) + 1))
            return (0);
    }
    return (1);
}

int   as_check_enough_params(t_list_error **error, char *line, int i)
{
    int pos;
    int k;

    pos = as_get_pos(0, 0);
    k = as_k(0);
    if (!k && !as_add_error(error, ERROR9, line, i + 1))
        return (0);
    if (k && k < op_tab[pos].param_count)
    {
        if (!as_add_error(error, ERROR18, line, i + 1))
            return (0);
        // ft_printf(BOLDWHITE "expected %d, have %d\n" RESET, op_tab[pos].param_count, k);
	    // as_write_err_line(line, i + 1);
	    // as_write_err_sign(line, i + 1);
    }
    return (1);
}

int     as_get_pos(unsigned char byte, int a)
{
    static int  pos = 0;

    if (a == 1)
        pos = 0;
    while (a == 1 && byte != op_tab[pos].opcode)
        pos++;
    return (pos);
}

int     as_j(int a, int i)
{
    static int j = 0;

    if (a == 1)
        j = i;
    return (j);
}

int     as_k(int a)
{
    static int k = 0;
    
    if (a == 1)
        k = 0;
    else if (a == 2)
        k++;
    return (k);
}
