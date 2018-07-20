/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_store2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/12 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int	as_store_non_zero(int length, char *line, int *i, t_list_byte **code)
{
	int	l;

	l = 0;
	while (l < length && line[*i] != '"')
	{
		if (!(as_add_byte(code, line[*i])))
        	return (0);
		(*i)++;
		l++;
	}
	return (1);
}

int	as_store_zero(int i, int section, t_list_byte **code)
{
	i = (section) ?
	(COMMENT_LENGTH - (as_code_size(*code) - PROG_NAME_LENGTH) + 16) :
	(PROG_NAME_LENGTH - as_code_size(*code) + 12);
	while (i)
	{
		if (!(as_add_byte(code, 0)))
    		return (0);
		i--;
	}
	return (1);
}

int	as_get_params(char *line, t_list_label **label, t_list_byte **code)
{
    int             i;
    t_list_byte     *encoding;
    int             byte_pos;

    byte_pos = as_code_size(*code) - 1;
    if (!as_gparams_init(&i, code, line, &encoding))
        return (0);
    while (line[i])
    {   
        as_j(1, i);
    	as_skip_to_sep(line, &i);
		as_k(2);
        if ((line[as_j(0, 0)] == 'r') && !as_s_reg(code, &encoding, line))
            return (0);
		if (as_dir(line) == 2 && as_enc(&encoding, 2) &&
		!as_dlabel(line, label, byte_pos, code))
            return (0);
        if (as_dir(line) == 1 && as_enc(&encoding, 2) && !as_sd(line, code))
			return (0);
		if (as_ind(line) == 2 && as_enc(&encoding, 5) &&
		!as_ilabel(line, label, byte_pos, code))
			return (0);
        if (as_ind(line) == 1 && as_enc(&encoding, 5) && !as_si(line, code))
			return (0);
        as_skip_space(line, &i);
		if (line[i])
			i++;
    }
    return (1);
}

int	as_get_command(char *line, int i, t_list_byte **code)
{
    int         j;

    j = as_get_op_pos(line, i);
    if (!(as_add_byte(code, (unsigned char)op_tab[j].opcode)))
        return (0);
    return (1);
}
