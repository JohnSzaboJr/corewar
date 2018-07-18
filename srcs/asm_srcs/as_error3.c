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

static void	as_putspace(char *line, int i)
{
	char	c;

	c = (ft_isspace(line[i])) ? (line[i]) : (' ');
	write(2, &c, 1);
}

static void	as_err_line_dots(char *line)
{
	char	c;

	c = line[MAX_ERROR_SIZE - 1];
	line[MAX_ERROR_SIZE - 1] = '\0';
	ft_putstr_fd(line, 2);
	ft_putstr_fd("...\n", 2);
	line[MAX_ERROR_SIZE - 1] = c;
}

void	as_write_err(char *message, int line_nr, int column_nr, int e)
{
	if (column_nr)
	{
		ft_putstr_fd(BOLDWHITE, 2);
		ft_putstr_fd("\nline ", 2);
		as_errnbr(line_nr);
		ft_putstr_fd(", column ", 2);
		as_errnbr(column_nr);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(RESET, 2);
	}
    if (e)
		ft_putstr_fd(BOLDRED "error:" RESET, 2);
    else
		ft_putstr_fd(BOLDMAGENTA "warning:" RESET, 2);
	ft_putstr_fd(BOLDWHITE, 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(RESET, 2);
}

static void	as_write_long_err(char *line, int column_nr)
{
	char c;

	c = line[MAX_ERROR_SIZE + column_nr - 6];
	line[MAX_ERROR_SIZE + column_nr - 6] = '\0';
	ft_putstr_fd(line + column_nr - 5, 2);
	ft_putstr_fd("...\n", 2);
	line[MAX_ERROR_SIZE + column_nr - 6] = c;	
}

void    as_write_err_line(char *line, int column_nr)
{
    if (ft_strlen(line) > MAX_ERROR_SIZE && column_nr < MAX_ERROR_SIZE)
		as_err_line_dots(line);
	else if (ft_strlen(line) > MAX_ERROR_SIZE && column_nr >= MAX_ERROR_SIZE)
	{
		ft_putstr_fd("...", 2);
		if (ft_strlen(line + column_nr - 5) > MAX_ERROR_SIZE)
			as_write_long_err(line, column_nr);
		else
		{
			ft_putstr_fd(line + column_nr - 5, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	else
	{
		ft_putstr_fd(line, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	as_write_err_sign(char *line, int column_nr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strlen(line) > MAX_ERROR_SIZE && column_nr >= MAX_ERROR_SIZE)
	{
		i = column_nr - 5;
		while (j < 7)
		{
			as_putspace(line, i);
			i++;
			j++;
		}
	}
	else
	{
		while (i < column_nr - 1)
		{
			as_putspace(line, i);
			i++;
		}
	}
	ft_putstr_fd(GREEN "^\n" RESET, 2);
}


char *as_get_err_par(int co, int k)
{
	if (op_tab[co].param_type[k - 1] == T_DIR)
		return (BOLDWHITE " direct" RESET);
	else if (op_tab[co].param_type[k - 1] == T_DIR + T_IND)
		return (BOLDWHITE " direct or indirect" RESET);
	else if (op_tab[co].param_type[k - 1] == T_REG)
		return (BOLDWHITE " register" RESET);
	else if (op_tab[co].param_type[k - 1] == T_IND + T_REG)
		return (BOLDWHITE " indirect or register" RESET);
	else if (op_tab[co].param_type[k - 1] == T_DIR + T_REG)
		return (BOLDWHITE " direct or register" RESET);
	return (NULL);
}

int	as_err_note3(int line_nr, int column_nr, char *message)
{
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDBLACK " note:" RESET);
    ft_printf(WHITE " switch this to a parameter of type" RESET);
    ft_printf("%s", message);
    ft_printf(WHITE " to silence this warning\n" RESET);
    return (1);
}

int	as_err_note4(int line_nr, int column_nr, char *message)
{
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDBLACK " note:" RESET);
    ft_printf(WHITE " did you mean '%s'?\n" RESET, message);
    return (1);
}

int	as_not1(int line_nr, int column_nr, char *message)
{
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDBLACK " note:" RESET);
    ft_printf(WHITE "%s" RESET, message);
    return (1);
}

int	as_err_note2(int line_nr, int column_nr)
{
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDBLACK " note:" RESET);
	ft_printf(WHITE " choose a non-zero register number that is not higher than %d to silence this warning\n" RESET, REG_NUMBER);
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