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
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

static int	as_store_size(t_list_byte **size, t_list_byte *code)
{
	int	s;
	int	i;

	i = 0;
	s = as_code_size(code) - PROG_NAME_LENGTH - COMMENT_LENGTH - 16;
	while (i < 4)
    {
        (*size)->byte = (s >> (8 * i)) & 0xff;
        (*size) = (*size)->next;
        i++;
    }
	return (1);
}

static int as_store_commands(char *line, t_list_byte **code, t_list_label **label)
{
	int				i;
	int				j;

	i = 0;
	as_skip_label2(line, &i);
	i = (line[i] == LABEL_CHAR) ? (i + 1) : (0);
	as_skip_space(line, &i);
	if (!line[i])
		return (1);
	j = as_get_command(line, i, code);
	if (!j)
		return (0);
	if (j != -1 && !as_get_params(line, label, code))
		return (0);
	return (1);
}

static int as_store_nc(char *line, int *sec, t_list_byte **code, t_list_byte **size)
{
	int			i;
	int			length;

	as_store_name_comment_init(line, &i, *sec, &length);
	if (!as_store_non_zero(length, line, &i, code) ||
	!as_store_zero(i, *sec, code))
		return (0);
	if (!(*sec))
		*size = *code;
	(*sec)++;
	return (1);
}

static int as_store_magic(t_list_byte **code)
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

int	as_store(int fd, t_list_label **label, char *filename)
{
	char			*line;
	int				sec;
	t_list_byte		*code;
	t_list_byte		*size;

	as_store_init(&line, &code, &size, &sec);
	if (!as_store_magic(&code))
		return (0);
	while (get_next_line(fd, &line))
	{
		as_endcomment(line, 0);
		if (line[0] && line[0] != COMMENT_CHAR)
		{
			if ((sec == 2 && !as_store_commands(line, &code, label)) ||
			((sec == 0 || sec == 1) && !as_store_nc(line, &sec, &code, &size)))
				return (as_free_line(line));
		}
		as_endcomment(line, 1);
		free(line);
	}
	free(line);
	if (!as_store_size(&size, code) || !as_reverse_list(&code) ||
	!as_write_file(&code, filename) || !as_free(&code))
		return (0);
	return (1);
}
