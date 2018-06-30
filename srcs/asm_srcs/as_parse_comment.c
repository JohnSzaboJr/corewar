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

int as_parse_comment(char *line, int *section, t_list_byte **code)
{
	if (!(ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))))
	{
		int         i;
		t_list_byte  *new;

		i = ft_strlen(COMMENT_CMD_STRING);
		while (ft_isspace(line[i]) || line[i] == '"')
			i++;
		while (line[i] != '"')
		{
			if (!(new = (t_list_byte *)malloc(sizeof(*new))))
				return (as_error(code, 2));
			new->next = *code;
			*code = new;
			(*code)->byte = line[i];
			i++;
		}
		(*section)++;
		return (1);
	}
	return (as_error(code, 3));
}
