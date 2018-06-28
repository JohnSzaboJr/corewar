/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/26 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

int as_parse_name(char *line, int *section, t_list_num **code)
{
    if (!(ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))))
    {
        int i;
        t_list_num *new;

        i = ft_strlen(NAME_CMD_STRING);
        i = i + 2;
        while (line[i] != '"')
        {
            if (!(new = (t_list_num *)malloc(sizeof(*new))))
            {
                as_free(code);
                ft_printf("%s\n", "ERROR: couldn't compile due to malloc error in as_parse_name");
                return (0);
            }
            new->next = *code;
            *code = new;
            (*code)->num = line[i];
            i++;
        }
        (*section)++;
        return (1);
    }
    ft_printf("%s\n", "ERROR: no name specified (or incorrectly specified) in source file");
    as_free(code);
    return (0);
}
