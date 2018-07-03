/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_check_quot.c                                    :+:      :+:    :+:   */
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
#include "as_errors.h"
#include <fcntl.h>

int	as_check_comment_quot2(int *i, int line_nr, char *line, t_list_byte **code)
{
	if (line[*i] != '"')
	{
		as_err1(ERROR6, line_nr, line, (*i) + 1);
		as_record_error(code);
		return (1);
	}
	return (0);
}

int	as_check_name_quot2(int *i, int line_nr, char *line, t_list_byte **code)
{
	if (line[*i] != '"')
	{
		as_err1(ERROR4, line_nr, line, (*i) + 1);
		as_record_error(code);
		return (1);
	}
	return (0);
}

int	as_check_comment_quot1(int *i, int line_nr, char *line, t_list_byte **code)
{
	if (!(line[*i]) || line[*i] != '"')
	{
		as_err1(ERROR5, line_nr, line, (*i) + 1);
		as_record_error(code);
		return (1);
	}
	return (0);
}

int	as_check_name_quot1(int *i, int line_nr, char *line, t_list_byte **code)
{
	if (!(line[*i]) || line[*i] != '"')
	{
		as_err1(ERROR2, line_nr, line, (*i) + 1);
		as_record_error(code);
		return (1);
	}
	return (0);
}
