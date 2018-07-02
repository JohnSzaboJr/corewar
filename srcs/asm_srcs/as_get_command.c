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
#include <fcntl.h>

int as_get_command(char *line, int i, t_list_byte **code, int line_nr)
{
    int         j;
    t_list_byte *new;
    char        c;
    int         k;
    int         l;

    j = 15;
    k = 0;
    while (j >= 0)
    {
        if (!ft_strncmp(op_tab[j].opname, line + i, ft_strlen(op_tab[j].opname)))
            break ;
        j--;
    }
    if (j == -1 || !ft_isspace(line[i + ft_strlen(op_tab[j].opname)]))
    {
        ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, i + 1);
        ft_printf(BOLDRED " error:" RESET);
        ft_printf(BOLDWHITE " unknown operation\n" RESET);
        ft_printf("%s\n", line);
        while (line[k] && ft_strchr(LABEL_CHARS, line[k]))
		    k++;
        l = k + 1;
        if (line[k] == LABEL_CHAR)
        {
            k++;
            while (k)
            {
                ft_putchar(' ');
                k--;
            }
            c = line[i];
            line[i] = '\0';
            ft_putstr(line + l);
            line[i] = c;
            ft_printf(GREEN "^\n" RESET);
        }
        else
        {
            c = line[i];
            line[i] = '\0';
            ft_putstr(line);
            line[i] = c;
            ft_printf(GREEN "^\n" RESET);
        }
        new = *code;
	    while ((*code)->next)
		    *code = (*code)->next;
	    (*code)->byte = 'Y';
	    *code = new;
    }
    else
    {
        // ezt rendesre, h lealljon a program, es proper error code
        if (!(new = (t_list_byte *)malloc(sizeof(*new))))
			return (as_error(code, 0));
        new->byte = (char)op_tab[j].opcode;
        new->next = *code;
        *code = new;
    }
    return (1);
}
