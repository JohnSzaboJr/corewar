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
	t_list_label	*new;

	i = 0;
	ret = 0;
	if (as_skip_label(line, &i) && line[i] == LABEL_CHAR)
	{
		if (!(new = (t_list_label *)malloc(sizeof(*new))))
		{
			as_free_label(label);
			return (as_error(code, 2));
		}
		if (!(new->name = ft_strnew(i)))
		{
			as_free_label(label);
			return (as_error(code, 2));
		}
		ft_strncpy(new->name, line, i);
		new->pos = as_code_size(*code);
		new->next = *label;
		*label = new;
		i++;
	}
	else
		i = 0;
	as_skip_space(line, &i);
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

	

	// I have to free labels as well!!! (also on errors)
	// parse potential labels (check if there label char)
	// save label name and byte position
	// can label names be the same as known commands?	
	return (1);
}

int as_parse_comment(char *line, int line_nr, int *section, t_list_byte **code)
{
	int			i;
	t_list_byte	*new;

	(*section)++;
	if (!(ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))) &&
		(ft_isspace(line[ft_strlen(COMMENT_CMD_STRING)]) ||
		line[ft_strlen(COMMENT_CMD_STRING)] == '"'))
	{
		if (as_parse_comment_check(&i, line, code, line_nr) &&
			!as_save_comment(&i, line, code, &new))
			return (0);
		i = COMMENT_LENGTH - (as_code_size(*code) - PROG_NAME_LENGTH) + 17;
		while (i)
		{
			if (!(new = (t_list_byte *)malloc(sizeof(*new))))
				return (as_error(code, 1));
			new->next = *code;
			*code = new;
			(*code)->byte = 0;
			i--;
		}
		return (1);
	}
	as_record_error(code);
	return (as_err1(ERROR7, line_nr, line, 1));
}

int as_parse_name(char *line, int line_nr, int *section, t_list_byte **code)
{
	int			i;
	t_list_byte	*new;

	(*section)++;
	if (!(ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))) &&
		(ft_isspace(line[ft_strlen(NAME_CMD_STRING)]) ||
		line[ft_strlen(NAME_CMD_STRING)] == '"'))
	{
		if (as_parse_name_check(&i, line, code, line_nr) &&
			!as_save_name(&i, line, code, &new))
			return (0);
		i = PROG_NAME_LENGTH - as_code_size(*code) + 13;
		while (i)
		{
			if (!(new = (t_list_byte *)malloc(sizeof(*new))))
				return (as_error(code, 0));
			new->next = *code;
			*code = new;
			(*code)->byte = 0;
			i--;
		}
		return (1);
	}
	as_record_error(code);
	return (as_err1(ERROR1, line_nr, line, 1));
}

int as_store_error(t_list_byte **code)
{
	t_list_byte	*new;

	if (!(new = (t_list_byte *)malloc(sizeof(*new))))
	{
		ft_printf(BOLDYELLOW "\nsystem error:" RESET);
		ft_printf(BOLDWHITE ERROR0 RESET);
		ft_printf(WHITE " (as_store_error)\n" RESET);
		as_free(code);
		return (0);
	}
	new->byte = 0;
	new->next = *code;
	*code = new;
	as_reverse_list(code);
	return (1);
}

int as_store_magic(t_list_byte **code)
{
	t_list_byte	*new;
	int			magic;
	int			i;

	i = 4;
	magic = COREWAR_EXEC_MAGIC;
	while (i)
	{
		if (!(new = (t_list_byte *)malloc(sizeof(*new))))
		{
			ft_printf(BOLDYELLOW "\nsystem error:" RESET);
			ft_printf(BOLDWHITE ERROR0 RESET);
			ft_printf(WHITE " (as_store_magic)\n" RESET);
			as_free(code);
			return (0);
		}
		new->byte = magic % 256;
		magic = (magic - (magic % (256))) / (256);
		new->next = *code;
		*code = new;
		i--;
	}
	return (1);
}
