/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/08 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

static int  as_arg_num(int argc)
{
    if (argc != 2)
    {
        ft_putstr_fd("usage: ./asm [champion filename]\n", 2);
        return (0);
    }
    return (1);
}

static int  as_open(char *filename, int *fd)
{
    if (0 > ((*fd) = open(filename, O_RDONLY)))
    {
        ft_putstr_fd("error: no such file: ", 2);
        ft_putstr_fd(filename, 2);
        ft_putstr_fd("\n", 2);
        return (0);
    }
    return (1);
}

static int  as_parse_errors_labels(int fd, t_list_label **label)
{
    char            *line;
    int             section;
    t_list_error    *error;
    int             byte_count;

    line = NULL;
    error = NULL;
    section = 0;
    byte_count = 4;

    while (get_next_line(fd, &line))
	{
        if (line[0] && line[0] != COMMENT_CHAR)
        {
            if ((section == 2 && !as_parse_el_commands(line, &error, &label, &byte_count)) ||
            (section == 1 && !as_parse_el_comment(line, &section, &error, &byte_count)) ||
            (section == 0 && !as_parse_el_name(line, &section, &error, &byte_count)))
            {
                free(line);
                return (0);
            }
        }
        free(line);
        as_line_nr(1);
    }
    //
    as_reverse_list(&code);
    as_print_list(code, label);
    //
    free(line);
    return (1);
}

int         main(int argc, char **argv)
{
    int             fd;
    t_list_label    *label;

    fd = 0;
    label = NULL;
    // atirni a programot innen.
    // 2x nyitni meg es parsingolni a file-t.
    // elso korben elmenteni az osszes hibat, warningot
    // es labelt, positionnal
    // masodik korben elmenteni a bytokat

    if (!as_arg_num(argc) || !as_open(argv[1], &fd) ||
    !as_parse_errors_labels(fd, &label))
    {
        as_free_label(&label);
        return (1):
    }

    close(fd);
    fd = 0;
    if (!as_open(argv[1], &fd) || !as_parse(fd))
        return (1);
    close(fd);
    return (0);
}
// free labels! free code!