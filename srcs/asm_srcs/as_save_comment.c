/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_save_comment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/01 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

int as_save_comment(int *i, char *line, t_list_byte **code, t_list_byte **new)
{
	while (line[*i] != '"')
	{
		if (!((*new) = (t_list_byte *)malloc(sizeof(**new))))
			return (as_error(code, 7));
		(*new)->next = *code;
		*code = *new;
		(*code)->byte = line[*i];
		(*i)++;
	}
	return (1);
}
