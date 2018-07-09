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

int as_get_params(char *line, t_list_label **label, t_list_byte **code, int line_nr)
{
    int             i;
    int             params;
    t_list_byte     *encoding;
    int             byte_pos;

    byte_pos = as_code_size(*code) - 1;
    if (-1 == (params = as_init_i_k_pos_params(&i, code, line, &encoding)))
        return (0);
    while (line[i] && params)
    {   
        as_bw_params(&i, line, code, line_nr);
        if (as_reg(line, line_nr, &i, code) && !as_s_reg(code, &encoding, line))
            return (0);
        if (as_dir(line) && as_dir_label(line, label, byte_pos, code) &&
        !as_s_label(code, &encoding, line))
            return (0);
        if (as_dir(line))
        {
            ft_printf("found direct\n");
        }
        if (ft_isdigit(line[as_j(0, 0)]) || line[as_j(0, 0)] == '-')
        {
            ft_printf("found indirect\n");
        }
        as_check_valid_params(line_nr, line);
        as_skip_to_next_param(line, line_nr, &i);
    }
    as_check_enough_params(code, line_nr, line, i);

    //
    if (!(*label))
        ft_printf("y\n");
    //
    return (1);
}

int as_get_command(char *line, int i, t_list_byte **code, int line_nr)
{
    int         j;
    int         error;

    j = 15;
    error = 0;
    while (j >= 0)
    {
        if (!ft_strncmp(op_tab[j].opname, line + i, ft_strlen(op_tab[j].opname)))
            break ;
        j--;
    }
    if (j > -1 && !line[i + ft_strlen(op_tab[j].opname)])
        j = 0;
    else if (j == -1 || !ft_isspace(line[i + ft_strlen(op_tab[j].opname)]))
        error = as_err1(ERROR8, line_nr, line, i + 1);
    else if (!(as_add_byte(code, (unsigned char)op_tab[j].opcode)))
        return (0);
    return (error) ? (-1) : (1);
}
