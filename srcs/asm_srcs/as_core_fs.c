/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_core_fs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/25 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

int as_arg_num(int argc)
{
    if (argc != 2)
    {
        ft_printf("%s\n", "usage: ./asm [champion filename]");
        return (0);
    }
    return (1);
}

int as_open(char *filename, int *fd)
{
    if (0 > ((*fd) = open(filename, O_RDONLY)))
    {
        ft_printf("%s%s\n", "error: no such file: ", filename);
        return (0);
    }
    return (1);
}

int as_parse(int fd)
{
    char            *line;
    int             section;
    int             line_nr;
    t_list_byte     *code;
    t_list_label    *label;

    line = NULL;
    code = NULL;
    label = NULL;
    section = 0;
    line_nr = 1;
    if (!as_store_magic(&code))
        return (0);
    while (get_next_line(fd, &line))
	{
        if (line[0] && line[0] != COMMENT_CHAR)
        {
            if ((section == 2 && !as_parse_commands(line, line_nr, &code, &label)) ||
            (section == 1 && !as_parse_comment(line, line_nr, &section, &code)) ||
            (section == 0 && !as_parse_name(line, line_nr, &section, &code)))
            {
                free(line);
                return (0);
            }
            // ft_printf("%s\n", line);
        }
        free(line);
        line_nr++;
    }
    //
    as_reverse_list(&code);
    as_print_list(code, label);
    //
    free(line);
    return (1);
}

    // store size at the end.
    // mi van ha directoryt ad meg
    // csinalni egy flaget h elnevezhesse aminek akarja