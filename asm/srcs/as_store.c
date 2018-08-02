/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/12 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm_struct.h"
#include "asm_prot.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

static int	as_ssize(t_list_byte **size, t_list_byte *code)
{
	int	s;
	int	i;

	i = 0;
	s = as_code_size(code) - PROG_NAME_LENGTH - COMMENT_LENGTH - 16;
	while (i < 4)
    {
		(*size)->type = 6;
        (*size)->byte = (s >> (8 * i)) & 0xff;
        (*size) = (*size)->next;
        i++;
    }
	return (1);
}

static int as_store_commands(char *l, t_list_byte **code, t_list_label **label, t_flags *f)
{
	int				i;
	int				j;

	i = 0;
	as_skip_label2(l, &i);
	i = (l[i] == LABEL_CHAR) ? (i + 1) : (0);
	as_skip_space(l, &i);
	if (!l[i])
		return (1);
	j = as_get_command(l, i, code, f);
	if (!j)
		return (0);
	if (j != -1 && !as_get_params(l, label, code, f))
		return (0);
	return (1);
}

static int as_store_nc(char *line, int *sec, t_list_byte **c, t_list_byte **s)
{
	int			i;
	int			length;
	int			ret;
	static int	suc = 0;

	ret = 0;
	if (!suc)
	{
		if (!line[0])
			return (1);
		as_store_name_comment_init(line, &i, *sec, &length);
	}
	else
	{
		i = 0;
		length = (*sec) ? COMMENT_LENGTH : PROG_NAME_LENGTH;
	}
	suc = 1;
	if (!(ret = as_store_non_zero(length, line, &i, c)))
		return (0);
	if (ret == 2)
	{
		if (!as_store_zero(i, *sec, c))
			return (0);
		if (!(*sec))
		*s = *c;
		suc = 0;
		(*sec)++;
	}
	return (1);
}

int			as_store_magic(t_list_byte **code)
{
	int			magic;
	int			i;

	i = 4;
	magic = COREWAR_EXEC_MAGIC;
	while (i)
	{
		if (!(as_add_byte(code, magic % 256, 0)))
        	return (0);
		magic = (magic - (magic % (256))) / (256);
		i--;
	}
	as_rlist(code);
	return (1);
}

int			as_store(int fd, t_list_label **label, char *filename, t_flags *f)
{
	char			*line;
	int				sec;
	t_list_byte		*code;
	t_list_byte		*size;

	if (!as_store_init(&line, &code, &size, &sec))
		return (0);
	while (get_next_line(fd, &line))
	{
		as_endcomment(line, 0);
		if (line[0] && line[0] != COMMENT_CHAR)
		{
			as_a_line(f, sec, code, line);
			if (sec == 2 && !as_store_commands(line, &code, label, f))
				return (as_free_line(line));
		}
		if ((sec == 0 || sec == 1) && !as_store_nc(line, &sec, &code, &size))
			return (as_free_line(line));
		as_endcomment(line, 1);
		free(line);
	}
	free(line);
	if (!as_ssize(&size, code) || !as_rlist(&code) ||
	(f->p && !as_plist(code)) || !as_wfile(&code, filename) || !as_free(&code))
		return (0);
	return (1);
}
