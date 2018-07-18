/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/18 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "as_errors.h"
#include "colors.h"
#include <fcntl.h>

int	as_empty_line_check(t_list_error **error, int a, char *line)
{
	static int el = 0;

	if (el > 1 && !a && !as_add_warning(error, WARNING13, line, 1))
		return (0);
	if (a == 2 && el && !as_add_warning(error, WARNING14, line, 1))
		return (0);
	if (a == 2 && el && !as_add_note(error, NOTE1, 1))
		return (0);
	if (a == 1)
		el++;
	if (a == 0)
		el = 0;
	return (1);
}

int	as_ec(char **line, t_list_error **error, int bc, int i)
{
	if (i < 3 && !as_add_error_noline(error, ERROR29))
		return (as_free_line(*line));
	if (bc - PROG_NAME_LENGTH - COMMENT_LENGTH - 16 >= MEM_SIZE / 4 &&
	!as_add_error_noline(error, ERROR32))
		return (as_free_line(*line));
	free(*line);
	as_reverse_error(error);
	if (as_print_error(*error))
		return (as_free_error(error));
	as_free_error(error);
	return (1);
}

int	as_lc(char *line, char *filename)
{
	if (!line)
		return (as_err2(ERROR31, filename));
	return (1);
}