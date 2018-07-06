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

void    as_check_valid_params(int line_nr, char *line)
{
    if (line[as_j(0, 0)] != 'r' && line[as_j(0, 0)] != DIRECT_CHAR &&
    !(ft_isdigit(line[as_j(0, 0)]) || line[as_j(0, 0)] == '-'))
        as_err1(ERROR11, line_nr, line, as_j(0, 0) + 1);
}

void    as_check_enough_params(t_list_byte **code, int line_nr, char *line, int i)
{
    int pos;
    int k;

    pos = as_get_pos((*code)->byte, 0);
    k = as_k(0);
    if (!k)
        as_err1(ERROR9, line_nr, line, i + 1);
    else if (k < op_tab[pos].param_count)
    {
        as_write_err(ERROR18, line_nr, i + 1, 1);
        ft_printf(BOLDWHITE "expected %d, have %d\n" RESET, op_tab[pos].param_count, k);
	    as_write_err_line(line, i + 1);
	    as_write_err_sign(line, i + 1);
        as_record_error(1);
    }
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
