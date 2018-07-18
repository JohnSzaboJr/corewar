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

int as_check_r(char *line, int *i, int j, t_list_error **error)
{
    int ret;

    ret = 0;
    as_skip_rev_space(line, i);
    if (!(ret = as_check_r_chars(line, *i, j, error)))
        return (0);
    if (ret != -1 && !(ret = as_check_r_length(line, *i, j, error)))
        return (0);
    if (ret != -1 && !(ret = as_check_r_zero(line, *i, j, error)))
        return (0);
    return (ret == -1) ? (-1) : (1);
}

int as_s_reg(t_list_byte **code, t_list_byte **encoding, char *line)
{
    if (as_enc(encoding, -1) &&
    !(as_add_byte(code, (unsigned char)ft_atoi(line + as_j(0, 0) + 1))))
        return (0);
    return (1);
}