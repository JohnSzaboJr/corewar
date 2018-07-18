/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_param.c                                         :+:      :+:    :+:   */
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

int	as_enc(t_list_byte **enc, int start)
{
	int			k;
	int			pos;
	const int	arr[9] = {64, 16, 4, 128, 32, 8, 192, 48, 12};

	k = as_k(0);
	pos = as_get_pos(0, 0);
	if (k <= op_tab[pos].param_count && *enc)
		(*enc)->byte = (*enc)->byte + (unsigned char)(arr[start + k]);
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

int    as_check_valid_params(t_list_error **error, char *line)
{
    if (line[as_j(0, 0)] != 'r' && line[as_j(0, 0)] != DIRECT_CHAR &&
    line[as_j(0, 0)] != LABEL_CHAR &&
    !(ft_isdigit(line[as_j(0, 0)]) || line[as_j(0, 0)] == '-'))
    {
        if (!as_add_error(error, ERROR11, line, as_j(0, 0) + 1))
            return (0);
    }
    return (1);
}

int   as_check_enough_params(t_list_error **error, char *line, int i)
{
    int pos;
    int k;

    pos = as_get_pos(0, 0);
    k = as_k(0);
    if (!k && !as_add_error(error, ERROR9, line, i + 1))
        return (0);
    if (k && k < op_tab[pos].param_count)
    {
        if (!as_add_error(error, ERROR18, line, i + 1))
            return (0);
        // ft_printf(BOLDWHITE "expected %d, have %d\n" RESET, op_tab[pos].param_count, k);
	    // as_write_err_line(line, i + 1);
	    // as_write_err_sign(line, i + 1);
    }
    return (1);
}

void	as_label_error(char *message, int lnr, char *line, int cnr)
{
	as_err1(ERROR28, lnr, line, cnr);
	if (message)
		as_note_label(lnr, cnr, message);
}