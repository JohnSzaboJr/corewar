/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/05 14:35:38 by jszabo           ###   ########.fr       */
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
	as_record_error(1);
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

int	as_record_error(int a)
{
	static int	i = 0;

	if (a)
		i++;
	return (i);
}