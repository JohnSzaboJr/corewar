/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse_comment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/26 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

int as_parse_comment(char *line, int line_nr, int *section, t_list_byte **code)
{
	int			i;
	int			length;
	t_list_byte	*new;

	(*section)++;
	if (!(ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))) &&
		(ft_isspace(line[ft_strlen(COMMENT_CMD_STRING)]) ||
		line[ft_strlen(COMMENT_CMD_STRING)] == '"'))
	{
		if (as_parse_comment_check(&i, line, code, line_nr) &&
			!as_save_comment(&i, line, code, &new))
			return (0);
		length = COMMENT_LENGTH - length + 4;
		while (length)
		{
			if (!(new = (t_list_byte *)malloc(sizeof(*new))))
				return (as_error(code, 0));
			new->next = *code;
			*code = new;
			(*code)->byte = 0;
			length--;
		}
		return (1);
	}
	return (as_error(code, 3));
}
