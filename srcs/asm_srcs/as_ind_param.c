/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_ind_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/03 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int as_ind_encoding(t_list_byte **encoding)
{
    int k;
    int pos;

    k = as_k(0);
    pos = as_get_pos(0, 0);
    if (k <= op_tab[pos].param_count && *encoding)
    {
        if (k == 1)
            (*encoding)->byte = (unsigned char)192;
        if (k == 2)
            (*encoding)->byte = (*encoding)->byte + (unsigned char)48;
        if (k == 3)
            (*encoding)->byte = (*encoding)->byte + (unsigned char)12;
    }
    return (1);
}

int as_store_ind(char *line, t_list_byte **code)
{
    int pos;
    int i;
    int j;
    char    c;
    int num;

    j = as_j(0, 0);
    i = j;
    while (line[j] == '-' || ft_isdigit(line[j]))
        j++;
    c = line[j];
    line[j] = '\0';
    num = ft_atoi(line + i);
    line[j] = c;
    pos = as_get_pos(0, 0);
    j = 0;
    i = IND_SIZE;
    while (j < i)
    {
        if (!as_add_byte(code, (num >> (8 * j)) & 0xff))
            return (0);
        j++;
    }
    return (1);
}