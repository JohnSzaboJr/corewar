/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/05 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int	as_err_note3(int line_nr, int column_nr, int co, int k)
{
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDBLACK " note:" RESET);
    ft_printf(WHITE " switch this to a parameter of type" RESET);
    if (op_tab[co].param_type[k - 1] == T_DIR)
		ft_printf(BOLDWHITE " direct" RESET);
	else if (op_tab[co].param_type[k - 1] == T_DIR + T_IND)
		ft_printf(BOLDWHITE " direct or indirect" RESET);
	else if (op_tab[co].param_type[k - 1] == T_REG)
		ft_printf(BOLDWHITE " register" RESET);
	else if (op_tab[co].param_type[k - 1] == T_IND + T_REG)
		ft_printf(BOLDWHITE " indirect or register" RESET);
	else if (op_tab[co].param_type[k - 1] == T_DIR + T_REG)
		ft_printf(BOLDWHITE " direct or register" RESET);
    ft_printf(WHITE " to silence this warning\n" RESET);
    return (1);
}

int	as_err_note2(int line_nr, int column_nr)
{
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDBLACK " note:" RESET);
	ft_printf(WHITE " choose a register number that fits in a byte to silence this warning\n" RESET);
	return (1);
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