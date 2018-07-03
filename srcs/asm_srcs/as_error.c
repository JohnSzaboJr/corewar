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

int as_error(t_list_byte **code, int error_code)
{
    as_free(code);
    ft_printf(BOLDYELLOW "\nsystem error:" RESET);
	ft_printf(BOLDWHITE ERROR0 RESET);
    if (error_code == 0)
        ft_printf(WHITE " (as_parse_name)\n" RESET);
    if (error_code == 1)
        ft_printf(WHITE " (as_parse_comment)\n" RESET);
    if (error_code == 2)
        ft_printf(WHITE " (as_parse_commands)\n" RESET);
    if (error_code == 3)
        ft_printf(WHITE " (as_get_command)\n" RESET);
    return (0);
}

int	as_err2(char *message, int line_nr, char *line, int column_nr)
{
	int		i;
	int		j;
	int		l;
	char	c;

	i = 0;
	j = 0;
	l = 0;
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDRED " error:" RESET);
	ft_printf(BOLDWHITE "%s" RESET, message);
	ft_printf("%s\n", line);
	j = as_skip_label(line, &i) + 1;
    if (line[i] == LABEL_CHAR)
		l = 1;
	if (line[i] == LABEL_CHAR)
		as_putnspace(i + 1);
	c = line[column_nr - 1];
	line[column_nr - 1] = '\0';
    if (!l)
		j = 0;
	while (line[j])
	{
		if (ft_isspace(line[j]))
			ft_putchar(line[j]);
		else
			ft_putchar(' ');
		j++;
	}
	line[column_nr - 1] = c;
    ft_printf(GREEN "^\n" RESET);
	as_err_note(line_nr, line, column_nr);
	return (1);
}

int	as_err1(char *message, int line_nr, char *line, int column_nr)
{
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDRED " error:" RESET);
	ft_printf(BOLDWHITE "%s" RESET, message);
	ft_printf("%s\n", line);
	as_putnspace(column_nr - 1);
	ft_printf(GREEN "^\n" RESET);
	return (1);
}

int as_war1(char *message, int line_nr, char *line, int column_nr)
{
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDMAGENTA " warning:" RESET);
	ft_printf(BOLDWHITE "%s" RESET, message);
	ft_printf("%s\n", line);
	as_putnspace(column_nr - 1);
	ft_printf(GREEN "^\n" RESET);
	return (1);
}
