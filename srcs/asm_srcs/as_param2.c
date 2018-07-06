/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_param2.c                                        :+:      :+:    :+:   */
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

void  as_bw_params(int *i, char *line, t_list_byte **code, int line_nr)
{
    as_j(1, *i);
    as_skip_to_sep(line, i);
    as_k(2);
    if (as_k(0) > op_tab[as_get_pos((*code)->byte, 0)].param_count)
        as_err1(ERROR16, line_nr, line, as_j(0, 0) + 1);
    if (line[*i] == SEPARATOR_CHAR && ft_isspace(line[*i - 1]))
        as_war1(WARNING8, line_nr, line, *i);
}
