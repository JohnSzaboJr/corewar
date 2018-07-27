/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_store3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/27 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int			as_store_non_zero(int length, char *line, int *i, t_list_byte **c)
{
	int	l;

	l = 0;
	while (l < length && line[*i] != '"')
	{
		if (!(as_add_byte(c, line[*i], 5)))
			return (0);
		(*i)++;
		l++;
	}
	return (1);
}

int			as_store_zero(int i, int section, t_list_byte **code)
{
	i = (section) ?
	(COMMENT_LENGTH - (as_code_size(*code) - PROG_NAME_LENGTH) + 16) :
	(PROG_NAME_LENGTH - as_code_size(*code) + 12);
	while (i)
	{
		if (!(as_add_byte(code, 0, 5)))
			return (0);
		i--;
	}
	return (1);
}
