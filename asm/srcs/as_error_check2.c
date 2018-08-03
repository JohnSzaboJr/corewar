/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error_check2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/08/03 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm_struct.h"
#include "asm_prot.h"
#include "as_errors.h"
#include "colors.h"
#include <fcntl.h>

static int	as_ccheck_init2(char *line, int *i, int *j)
{
	as_endcomment(line, 1);
	*i = 0;
	if (!as_skip_name(line, i, j))
	{
		as_err1(ERROR17, as_line_nr(0), line, *j + 1);
		return (0);
	}
	return (1);
}

int			as_comment_check(int *i, char *line, t_list_error **error, int *bc)
{
	int			j;
	static int	comment = 0;
	static int	length = 0;
	int			ret;

	if (!comment)
	{
		as_ccheck_init(bc, i, &j, line);
		if (((j == *i && !as_add_warning(error, WARNING4, line, j + 1))) ||
		!as_set_nline_c(i, error, line, &comment))
			return (0);
		if ((ret = as_ccheck1(line, i, &j, error)) != 1)
			return (ret);
		length = (*i) - j;
		if (((*i) - j) && line[*i] == '"')
			return (as_clength_e(length, error, line, i));
	}
	else
	{
		if ((ret = as_ccheck_init2(line, i, &j)) != 1)
			return (ret);
		length = length + (*i) - j + 1;
		return (as_c_end(length, error, line, i));
	}
	return (1);
}

int			as_name_check(int *i, char *line, t_list_error **error, int *bc)
{
	int			j;
	static int	name = 0;
	static int	length = 0;
	int			ret;

	if (!name)
	{
		as_ncheck_init(bc, i, &j, line);
		if (((j == *i && !as_add_warning(error, WARNING1, line, j + 1))) ||
		!as_set_nline_n(i, error, line, &name))
			return (0);
		if ((ret = as_ncheck1(line, i, &j, error)) != 1)
			return (ret);
		length = (*i) - j;
		if (((*i) - j) && line[*i] == '"')
			return (as_nlength_e(length, error, line, i));
	}
	else
	{
		if ((ret = as_ccheck_init2(line, i, &j)) != 1)
			return (ret);
		length = length + (*i) - j + 1;
		return (as_n_end(length, error, line, i));
	}
	return (1);
}
