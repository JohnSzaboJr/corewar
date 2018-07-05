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
    int             i;
    int             j;
    int             k;
    unsigned char   command;
    t_list_byte     *encoding;
    char            c;

    i = 0;
    j = 0;
    k = 0;
    command = (*code)->byte;
    i = as_skip_label(line, &i) + 1;
    as_skip_space(line, &i);
    as_skip_command(line, &i);
    as_skip_space(line, &i);
    if (!line[i])
    {
        as_err1(ERROR9, line_nr, line, i + 1);
        as_record_error(code);
        return (1);
    }
    if (!(as_add_byte(code, 0)))
        return (0);
    encoding = *code;

    while (line[i])
    {   
        j = i;
        while (line[i] && line[i] != SEPARATOR_CHAR)
            i++;
        k++;
        if (line[i] == SEPARATOR_CHAR && ft_isspace(line[i - 1]))
            as_war1(WARNING8, line_nr, line, i);
        if (line[j] == 'r')
        {
            if (!line[j + 1])
            {
                as_err1(ERROR12, line_nr, line, j + 1);
                as_record_error(code);
            }
            else
            {
                while (ft_isspace(line[i - 1]))
                    i--;
                c = line[i];
                line[i] = '\0';
                if (line[j + 1] == '-' || ft_hasnondigits(line + j + 1))
                {
                    line[i] = c;
                    as_err1(ERROR11, line_nr, line, j + 1);
                    as_record_error(code);
                }
                else if (ft_atoi(line + j + 1) > 255 || ft_strlen(line + j + 1) > 3)
                {
                    line[i] = c;
                    as_err1(ERROR13, line_nr, line, j + 2);
                    as_record_error(code);
                    as_err_note2(line_nr, j + 2);
                }
                else if (!ft_atoi(line + j + 1))
                {
                    line[i] = c;
                    as_err1(ERROR14, line_nr, line, j + 2);
                    as_record_error(code);
                    as_err_note2(line_nr, j + 2);
                }
                else
                {
                    if (k == 1)
                        encoding->byte = (unsigned char)64;
                    if (k == 2)
                        encoding->byte = encoding->byte + (unsigned char)16;
                    if (k == 3)
                        encoding->byte = encoding->byte + (unsigned char)4;
                    if (!(as_add_byte(code, (unsigned char)ft_atoi(line + j + 1))))
                        return (0);
                    line[i] = c;
                }
                as_skip_space(line, &i);
            }
            // 
            ft_printf("found register\n");
        }
        else if (line[j] == DIRECT_CHAR)
        {
            ft_printf("found direct\n");
        }
        else if (ft_isdigit(line[j]) || line[j] == '-')
        {
            ft_printf("found indirect\n");
        }
        else
        {
            as_err1(ERROR11, line_nr, line, j + 1);
            as_record_error(code);
        }
        if (line[i])
            i++;
        as_skip_space(line, &i);
        // az a baj h enter is lehet!
         // record how many spaces skipped?
        // if not correct->warning
        // invalid characters at end?
    }

    // error: nem megfelelo tipus
    // error: too few argumentsn for operation
    // error: invalid argument
    // szamon tartani h mennyit talaltunk! es error ha tul sok
    if (*label)
        ft_printf("yeah\n");
    if (!(line[i]))
        ft_printf("-------------------------------------\n");
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
