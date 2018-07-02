/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse_name_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/02 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "as_errors.h"
#include <fcntl.h>

int as_parse_name_check(int *i, char *line, t_list_byte **code, int line_nr)
{
	int			j;
	int			error;

	error = 0;
	*i = ft_strlen(NAME_CMD_STRING);
	j = *i;
	as_skip_space(line, i);
	as_check_name_space(j, i, line_nr, line);
	as_check_name_quot1(i, line_nr, line, &error);
	as_skip_name(line, i, &j);
	if (!((*i) - j))
	{
		as_err1(ERROR3, line_nr, line, (*i) + 1);
		error = 1;
	}
	as_check_name_quot2(i, line_nr, line, &error);
	as_check_after_name(i, line_nr, line);
	if (((*i) - j) > PROG_NAME_LENGTH)
		as_war1(WARNING3, line_nr, line, (*i) + 1);
	*i = j;
	if (error)
		as_record_error(code);
	return (error) ? (0) : (1);
}
