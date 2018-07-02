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
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int as_parse_name(char *line, int line_nr, int *section, t_list_byte **code)
{
	int			i;
	int			length;
	t_list_byte	*new;

	(*section)++;
	if (!(ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))) &&
		(ft_isspace(line[ft_strlen(NAME_CMD_STRING)]) ||
		line[ft_strlen(NAME_CMD_STRING)] == '"'))
	{
		if (as_parse_name_check(&i, line, code, line_nr) &&
			!as_save_name(&i, line, code, &new))
			return (0);
		length = PROG_NAME_LENGTH - as_code_size(*code) + 13;
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
	as_record_error(code);
	return (as_err1(ERROR1, line_nr, line, 1));
}
