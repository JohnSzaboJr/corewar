/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/01 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int as_get_params(char *line, t_list_label **label, t_list_byte **code, int line_nr)
{
    int i;
    int j;

    i = 0;
    j = 0;
    i = as_skip_label(line, &i) + 1;
    as_skip_space(line, &i);
    as_skip_command(line, &i);
    as_skip_space(line, &i);
    if (!line[i])
    {
        as_err1(ERROR9, line_nr, line, i + 1);
        as_record_error(code);
    }
    if (!(as_add_byte(code, 0)))
        return (0);
    j = i;
    while (line[i] && line[i] != SEPARATOR_CHAR)
        i++;
    if (line[i] == SEPARATOR_CHAR && ft_isspace(line[i - 1]))
        as_war1(WARNING8, line_nr, line, i);
    if (line[j] == 'r')
    {
        ft_printf("found register\n");
    }
    
    
    // szamon tartani h mennyit talaltunk! es error ha tul sok
    ft_printf("%s\n", line + i);
    if ((*label) && (*code))
        line_nr = 0;
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
    {
        error = as_err1(ERROR8, line_nr, line, i + 1);
        as_record_error(code);
    }
    else if (!(as_add_byte(code, (unsigned char)op_tab[j].opcode)))
        return (0);
    return (error) ? (-1) : (1);
}
