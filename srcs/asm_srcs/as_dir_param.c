/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_dir_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/06 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int as_store_dir(char *line, t_list_byte **code)
{
    int pos;
    int i;
    int j;
    char    c;
    int num;

    j = as_j(0, 0) + 2;
    as_skip_space(line, &j);
    i = j;
    while (line[j] == '-' || ft_isdigit(line[j]))
        j++;
    c = line[j];
    line[j] = '\0';
    num = ft_atoi(line + i);
    line[j] = c;
    pos = as_get_pos(0, 0);
    j = 0;
    i = (pos == 10) ? IND_SIZE : DIR_SIZE;
    while (j < i)
    {
        if (!as_add_byte(code, (num >> (8 * j)) & 0xff))
            return (0);
        j++;
    }
    return (1);
}

int  as_cmp_label(t_list_label *label, char *line, int k)
{
    while (label)
    {
        if (!ft_strcmp(line + k, label->name))
            return (label->pos);
        label = label->next;
    }
    return (0);
}

int as_dir_label2(char *line, t_list_label **label, int byte_pos, t_list_byte **code)
{
    int     j;
    int     k;
    char    c;
    int     i;
    t_list_byte *node;

    i = 2;
    j = as_j(0, 0);
    j = j + 2;
    as_skip_space(line, &j);
    k = j;
    as_skip_label(line, &j);
    c = line[j];
    line[j] = '\0';
    while (i)
    {
        if (!as_add_byte(code, 0))
            return (0);
        i--;
    }
    byte_pos = (as_cmp_label(*label, line, k)) - byte_pos;
    node = (*code);
    while (i < 2)
    {
        (*code)->byte = (byte_pos >> (8 * i)) & 0xff;
        (*code) = (*code)->next;
        i++;
    }
    (*code) = node;
    line[j] = c;
    return (1);
}

int as_dir_encoding(t_list_byte **encoding)
{
    int k;
    int pos;

    k = as_k(0);
    pos = as_get_pos(0, 0);
    if (k <= op_tab[pos].param_count && *encoding)
    {
        if (k == 1)
            (*encoding)->byte = (unsigned char)128;
        if (k == 2)
            (*encoding)->byte = (*encoding)->byte + (unsigned char)32;
        if (k == 3)
            (*encoding)->byte = (*encoding)->byte + (unsigned char)8;
    }
    return (1);
}

int as_dir_label(char *line)
{
    int j;

    j = as_j(0, 0);
    if (line[j] == DIRECT_CHAR && line[j + 1] && line[j + 1] == LABEL_CHAR)
        return (1);
    return (0);
}

int as_dir(char *line)
{
    if (line[as_j(0, 0)] == DIRECT_CHAR)
        return (1);
    return (0);
}