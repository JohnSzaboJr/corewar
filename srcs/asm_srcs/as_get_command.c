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

    i = 0;
    i = as_skip_label(line, &i) + 1;
    as_skip_space(line, &i);
    as_skip_command(line, &i);
    as_skip_space(line, &i);
    if (!line[i])
    {
        as_err2(ERROR9, line_nr, line, i + 1);
        as_record_error(code);
    }
    
    //ide masik tipusu hiba kell majd h ne legyen note veletlenul se!
    //atnezni a megnyitott fileokat, h milyen hosszuak a functionok
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
    t_list_byte *new;

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
        error = as_err2(ERROR8, line_nr, line, i + 1);
        as_record_error(code);
    }
    else
    {
        if (!(new = (t_list_byte *)malloc(sizeof(*new))))
			return (as_error(code, 3));
        new->byte = (char)op_tab[j].opcode;
        new->next = *code;
        *code = new;
    }
    return (error) ? (-1) : (1);
}
