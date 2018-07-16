/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error_print2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/16 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int	as_err1(char *message, int line_nr, char *line, int column_nr)
{
	as_write_err(message, line_nr, column_nr, 1);
	if (column_nr)
	{
		as_write_err_line(line, column_nr);
		as_write_err_sign(line, column_nr);
	}
	return (1);
}

int	as_err2(char *message, char *filename)
{
	ft_putstr_fd(BOLDYELLOW "file error: " RESET, 2);
	ft_putstr_fd(BOLDWHITE, 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

int	as_err3(char *message)
{
	ft_putstr_fd(BOLDGREEN "usage: " RESET, 2);
	ft_putstr_fd(WHITE, 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(RESET, 2);
	return (0);
}

int as_war1(char *message, int line_nr, char *line, int column_nr)
{
	as_write_err(message, line_nr, column_nr, 0);
	as_write_err_line(line, column_nr);
	as_write_err_sign(line, column_nr);
	return (1);
}
