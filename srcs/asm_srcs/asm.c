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

static int	as_open_close(int argc, char *filename, int *fd, int a)
{
	int	l;

	if (a)
	{
		if (close(*fd) < 0)
			return (as_err2(ERROR34, filename));
		return (1);
	}
	l = ft_strlen(filename);
	(*fd) = open(filename, O_RDONLY);
	if ((*fd) < 0)
		return (as_err2(ERROR30, filename));
	if (l <= 2 || (filename[l - 1] != 's' && filename[l - 1] != '.'))
		return (as_err2(ERROR31, filename));
	return (1);
}

static int	as_parse(int fd, t_list_label **label, char *filename, t_flags *flags)
{
	char			*line;
	t_list_error	*error;
	int				bc;
	int				i;

	i = as_parse_init(&line, &error, &bc);
	while (as_empty_line(get_next_line(fd, &line)) && line)
	{
		as_endcomment(line, 0);
		if (!as_parse_loop(line, &error, label, &bc))
			return (0);
		if (line[0] != COMMENT_CHAR)
			i++;
		if (!as_unexp_check(&error, line))
			return (0);
		as_endcomment(line, 1);
		free(line);
		as_line_nr(1);
	}
	if (!as_empty_line_check(&error, 2, line))
		return (as_free_line(line));
	if (!as_lc(line, filename) || !as_ec(&line, &error, bc, i) ||
	as_print_error(&error, label, flags) || as_free_error(&error))
		return (0);
	return (1);
}

int	as_write_file(t_list_byte **code, char *filename)
{
	int		fd;
	char	*newname;
	int		l;

	l = ft_strlen(filename);
	if (!(newname = ft_strnew(l + 2)))
		return (as_malloc_error2(code));
	ft_strncpy(newname, filename, l - 1);
	ft_strcpy(newname + l - 1, "cor");
	fd = open(newname, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR |
	S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		as_free(code);
		return (as_err2(ERROR36, newname));
	}
	while (*code)
	{
		write(fd, &((*code)->byte), 1);
		(*code) = (*code)->next;
	}
	ft_printf("Writing output program to %s\n", newname);
	free(newname);
	return (1);
}

static int	as_flags_init(t_flags **flags, int argc, char **argv, int *pos)
{
	int	i;

	i = 1;
	if (!(*flags = (t_flags *)(malloc(sizeof(**flags)))))
		return (0);
	// error message!
	// free the flags everywhere!
	(*flags)->w = 0;
	while (*pos < argc && argv[*pos][0] == '-')
		(*pos)++;
	if (argc < 2 || (*pos) == argc)
		return (as_err3(USAGE));
	while (i < argc)
	{
		if ((argv[i][0] != '-' || ft_strlen(argv[i]) != 2) && i != (*pos))
			return (as_err3(USAGE));
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'w' && !((*flags)->w))
				(*flags)->w = 1;
			else
				return (as_err3(USAGE));
		}
		i++;
	}
	return (1);
}

int			main(int argc, char **argv)
{
	int				fd;
	t_list_label	*label;
	t_flags			*flags;
	int				pos;

	fd = 0;
	pos = 1;
	label = NULL;
	if (!as_flags_init(&flags, argc, argv, &pos) ||
	!as_open_close(argc, argv[pos], &fd, 0) ||
	!as_parse(fd, &label, argv[pos], flags) ||
	!as_open_close(0, argv[pos], &fd, 1) ||
	!as_open_close(argc, argv[pos], &fd, 0) ||
	!as_store(fd, &label, argv[pos]) ||
	!as_open_close(0, argv[pos], &fd, 1))
		return (as_free_label(&label));
	as_free_label(&label);
	return (0);
}
