/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/03 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int as_parse_commands(char *line, int line_nr, t_list_byte **code, t_list_label **label)
{
	int				i;
	int				ret;

	i = 0;
	ret = 0;
	if (ft_strlen(line) > MAX_LINE_LENGTH)
	{
		as_err1(ERROR17, line_nr, line, 1);
		return (1);
	}
	if (as_skip_label(line, &i) && line[i] == LABEL_CHAR && i <= LABEL_SIZE)
	{
		if (!as_add_label(label, line, i, as_code_size(*code)))
		{
			as_free(code);
			return (0);
		}
		i++;
	}
	else if (i > LABEL_SIZE)
	{
		as_err1(ERROR10, line_nr, line, i + 1);
		i++;
	}
	else
		i = 0;
	as_skip_space(line, &i);
	if (!line[i])
		return (1);
	if (!(ret = as_get_command(line, i, code, line_nr)))
	{
		as_free_label(label);
		return (0);	
	}
	if (ret > -1 && !as_get_params(line, label, code, line_nr))
	{
		as_free_label(label);
		return (0);	
	}

	

	// can label names be the same as known commands?	
	return (1);
}

int as_parse_comment(char *line, int line_nr, int *section, t_list_byte **code)
{
	int			i;

	(*section)++;
	if (!(ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))) &&
		(ft_isspace(line[ft_strlen(COMMENT_CMD_STRING)]) ||
		line[ft_strlen(COMMENT_CMD_STRING)] == '"'))
	{
		if (as_parse_comment_check(&i, line, line_nr) &&
			!as_save_comment(&i, line, code))
			return (0);
		i = COMMENT_LENGTH - (as_code_size(*code) - PROG_NAME_LENGTH) + 16;
		while (i)
		{
			if (!(as_add_byte(code, 0)))
        		return (0);
			i--;
		}
		return (1);
	}
	return (as_err1(ERROR7, line_nr, line, 1));
}

int as_parse_name(char *line, int line_nr, int *section, t_list_byte **code)
{
	int			i;

	(*section)++;
	if (!(ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))) &&
		(ft_isspace(line[ft_strlen(NAME_CMD_STRING)]) ||
		line[ft_strlen(NAME_CMD_STRING)] == '"'))
	{
		if (as_parse_name_check(&i, line, line_nr) &&
			!as_save_name(&i, line, code))
			return (0);
		i = PROG_NAME_LENGTH - as_code_size(*code) + 12;
		while (i)
		{
			if (!(as_add_byte(code, 0)))
        		return (0);
			i--;
		}
		return (1);
	}
	return (as_err1(ERROR1, line_nr, line, 1));
}

int as_store_magic(t_list_byte **code)
{
	int			magic;
	int			i;

	i = 4;
	magic = COREWAR_EXEC_MAGIC;
	while (i)
	{
		if (!(as_add_byte(code, magic % 256)))
        	return (0);
		magic = (magic - (magic % (256))) / (256);
		i--;
	}
	as_reverse_list(code);
	return (1);
}
