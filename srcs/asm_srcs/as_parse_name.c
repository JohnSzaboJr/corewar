/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse_name.c                                    :+:      :+:    :+:   */
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

int as_parse_name(char *line, int *section, t_list_byte **code)
{
	int			i;
	int			length;
	t_list_byte	*new;

	if (!(ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))))
	{
		if (!as_parse_name_check(&i, line, code, &length) ||
			!as_save_name(&i, line, code, &new))
			return (0);
		length = PROG_NAME_LENGTH - length + 8;
		while (length)
		{
			if (!(new = (t_list_byte *)malloc(sizeof(*new))))
				return (as_error(code, 0));
			new->next = *code;
			*code = new;
			(*code)->byte = 0;
			length--;
		}
		(*section)++;
		return (1);
	}
	return (as_error(code, 1));
}
