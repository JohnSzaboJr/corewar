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
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int as_save_comment(int *i, char *line, t_list_byte **code, t_list_byte **new)
{
	int l;

	l = 0;
	while (l < COMMENT_LENGTH && line[*i] != '"')
	{
		if (!((*new) = (t_list_byte *)malloc(sizeof(**new))))
		{
			ft_printf(BOLDYELLOW "\nsystem error:" RESET);
			ft_printf(BOLDWHITE ERROR0 RESET);
			ft_printf(WHITE " (as_save_comment)\n" RESET);
			as_free(code);
			return (0);
		}
		(*new)->next = *code;
		*code = *new;
		(*code)->byte = line[*i];
		(*i)++;
		l++;
	}
	return (1);
}
