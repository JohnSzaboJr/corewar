/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/03 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int as_check_error(t_list_byte *code)
{
	while (code->next)
		code = code->next;
	if (code->byte == 'Y')
		return (1);
	return (0);
}

int	as_err_note(int line_nr, char *line, int column_nr)
{
	int	j;
	int	highest;
	int	pos;
	int	save;

	j = 15;
	highest = 0;
	pos = -1;
    while (j >= 0)
    {
        if ((save = as_cmd_comp(op_tab[j].opname, line + column_nr - 1)) > highest)
		{
			pos = j;
			highest = save;
		}
        j--;
    }
	if (highest > 1)
	{
		ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
		ft_printf(BOLDBLACK " note:" RESET);
		ft_printf(WHITE " did you mean '%s'?\n" RESET, op_tab[pos].opname);
	}
	return (1);
}

int	as_err1(char *message, int line_nr, char *line, int column_nr)
{
	as_write_err(message, line_nr, column_nr, 1);
	as_write_err_line(line, column_nr);
	as_write_err_sign(line, column_nr);
	if (message[1] == 'u')
		as_err_note(line_nr, line, column_nr);
	return (1);
}

int as_war1(char *message, int line_nr, char *line, int column_nr)
{
	as_write_err(message, line_nr, column_nr, 0);
	as_write_err_line(line, column_nr);
	as_write_err_sign(line, column_nr);
	return (1);
}
