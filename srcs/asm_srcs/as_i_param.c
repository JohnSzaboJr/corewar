/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_i_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/18 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

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

int as_ind_label(char *line, t_list_label **label, int byte_pos, t_list_byte **code)
{
    int     j;
    int     k;
    char    c;
    int     i;
    t_list_byte *node;

    i = 2;
    j = as_j(0, 0) + 1;
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

int as_ienc(t_list_byte **encoding)
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

int	as_ind(char *line)
{
	int j;

	j = as_j(0, 0);
	if (line[j] == LABEL_CHAR)
		return (2);
	else if (ft_isdigit(line[j]) || line[j] == '-')
        return (1);
	return (0);
}
