/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/12 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "as_errors.h"
#include "colors.h"
#include <fcntl.h>

static int  as_open(int argc, char *filename, int *fd)
{
	int	l;

	if (argc != 2)
		return (as_err3(USAGE));
	l = ft_strlen(filename);
	(*fd) = open(filename, O_RDONLY);
	if ((*fd) < 0)
		return (as_err2(ERROR30, filename));
	if (l <= 2 || (filename[l - 1] != 's' && filename[l - 1] != '.'))
		return (as_err2(ERROR31, filename));
	return (1);
}

static int	as_parse_end_check(char **line, t_list_error **error, int bc, int i)
{
	if (i < 3 && !as_add_error_noline(error, ERROR29))
		return (as_free_line(*line));
	if (bc - PROG_NAME_LENGTH - COMMENT_LENGTH - 16 >= MEM_SIZE / 4 &&
	!as_add_error_noline(error, ERROR32))
        return (as_free_line(*line));
	free(*line);
	as_reverse_error(error);
	if (as_print_error(*error))
		return (as_free_error(error));
	as_free_error(error);
	return (1);
}

static int  as_parse(int fd, t_list_label **label, char *filename)
{
	char            *line;
	int             sec;
	t_list_error    *error;
	int             bc;
	int				i;

	i = as_parse_init(&line, &error, &sec, &bc);
	while (get_next_line(fd, &line) && line)
	{
		if (line[0] && line[0] != COMMENT_CHAR)
		{
			if ((sec == 2 && !as_parse_commands(line, &error, label, &bc)) ||
			(sec == 1 && !as_parse_comment(line, &sec, &error, &bc)) ||
			(sec == 0 && !as_parse_name(line, &sec, &error, &bc)))
				return (as_free_line(line));
			i++;
		}
		free(line);
		as_line_nr(1);
	}
	if (!line)
		return (as_err2(ERROR31, filename));
	if (!as_parse_end_check(&line, &error, bc, i))
		return (0);
	return (1);
}

static int  as_store(int fd, t_list_label **label)
{
	char            *line;
	int             section;
	t_list_byte     *code;
	t_list_byte		*size;

	as_store_init(&line, &code, &size, &section);
	if (!as_store_magic(&code))
		return (0);
	while (get_next_line(fd, &line))
	{
		if (line[0] && line[0] != COMMENT_CHAR)
		{
			if ((section == 2 && !as_store_commands(line, &code, label)) ||
			((section == 0 || section == 1) &&
			!as_store_name_comment(line, &section, &code, &size)))
				return (as_free_line(line));
		}
		free(line);
	}
	free(line);
	as_store_size(&size, code);
	as_reverse_list(&code);
	//
	as_print_list(code, *label);
	//as_write_to_file(&code, name);
	free(&code);
	return (1);
}

int         main(int argc, char **argv)
{
	int             fd;
	t_list_label    *label;

	fd = 0;
	label = NULL;
	if (!as_open(argc, argv[1], &fd) ||
	!as_parse(fd, &label, argv[1]) ||
	close(fd) < 0 ||
	!as_open(argc, argv[1], &fd) ||
	!as_store(fd, &label) ||
	close(fd) < 0)
		return (as_free_label(&label));
	as_free_label(&label);
	return (0);
}
