/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/17 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "as_errors.h"
#include "colors.h"
#include <fcntl.h>

static int	as_open(int argc, char *filename, int *fd)
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

static int	as_parse_loop(
char *line, t_list_error **error, t_list_label **label, int *bc)
{
	static int	sec = 0;

	if (line[0] != COMMENT_CHAR)
	{
		if (!line[0])
			as_empty_line_check(error, 1, line);
		else
		{
			if (!as_empty_line_check(error, 0, line))
				return (as_free_line(line));
			if ((sec == 2 && !as_p_ops(line, error, label, bc)) ||
			(sec == 1 && !as_pcomment(line, &sec, error, bc)) ||
			(sec == 0 && !as_pname(line, &sec, error, bc)))
				return (as_free_line(line));
		}
	}
	return (1);
}

static int	as_parse(int fd, t_list_label **label, char *filename)
{
	char			*line;
	t_list_error	*error;
	int				bc;
	int				i;

	i = as_parse_init(&line, &error, &bc);
	while (as_empty_line(get_next_line(fd, &line)) && line)
	{
		if (!as_parse_loop(line, &error, label, &bc))
			return (0);
		if (line[0] != COMMENT_CHAR)
			i++;
		if (!as_unexp_check(&error, line))
			return (0);
		free(line);
		as_line_nr(1);
	}
	if (!as_empty_line_check(&error, 2, line))
		return (as_free_line(line));
	if (!as_lc(line, filename) || !as_ec(&line, &error, bc, i) ||
	as_print_error(&error, label))
		return (0);
	as_free_error(&error);
	return (1);
}

static int	as_store(int fd, t_list_label **label)
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
		if (line[0] && line[0] != COMMENT_CHAR)
		{
			if ((sec == 2 && !as_store_commands(line, &code, label)) ||
			((sec == 0 || sec == 1) && !as_store_nc(line, &sec, &code, &size)))
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

int			main(int argc, char **argv)
{
	int				fd;
	t_list_label	*label;

	fd = 0;
	label = NULL;
	if (!as_open(argc, argv[1], &fd) ||
	!as_parse(fd, &label, argv[1]) ||
	!as_close(fd, argv[1]) ||
	!as_open(argc, argv[1], &fd) ||
	!as_store(fd, &label) ||
	!as_close(fd, argv[1]))
		return (as_free_label(&label));
	as_free_label(&label);
	return (0);
}
