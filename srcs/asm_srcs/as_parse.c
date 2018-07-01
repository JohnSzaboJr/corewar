/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse.c                                         :+:      :+:    :+:   */
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

int as_parse(int fd)
{
    char            *line;
    int             section;
    t_list_byte     *code;
    t_list_label    *label;

    line = NULL;
    code = NULL;
    label = NULL;
    section = 0;
    if (!as_store_magic(&code))
        return (0);
    while (get_next_line(fd, &line))
	{
        if (line[0] && line[0] != COMMENT_CHAR)
        {
            // if ((section == 2 && !as_parse_commands(line, &section, &code)) ||
            if ((section == 1 && !as_parse_comment(line, &section, &code)) ||
            (section == 0 && !as_parse_name(line, &section, &code)))
            {
                free(line);
                return (0);
            }
            ft_printf("%s\n", line);
        }
        free(line);
    }
    //
    as_reverse_list(&code);
    as_print_list(code);
    //
    free(line);
    return (1);
}
    // make sure there is a .name and .comment
    // as specified in the header
    // control length of name and comment
    // store size at the end.