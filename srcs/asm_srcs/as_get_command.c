/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/06 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int  as_init_i_k_pos_params(int *i, t_list_byte **code, char *line, t_list_byte **encoding)
{
    *i = 0;
    as_k(1);
    as_get_pos((*code)->byte, 1);
    if (!(as_add_byte(code, 0)))
        return (-1);
    *encoding = *code;
    if (!as_skip_to_params(line, i))
        return (0);
    return (1);
}
