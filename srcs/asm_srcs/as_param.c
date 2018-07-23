/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/18 14:35:38 by jszabo           ###   ########.fr       */
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

int	as_cmp_label(t_list_label *label, char *line, int k)
{
	while (label)
	{
		if (!ft_strcmp(line + k, label->name))
			return (label->pos);
		label = label->next;
	}
	return (0);
}

int	as_slabel(char *line, int *i, t_list_error **error, t_list_label **label)
{
	char c;

	if (as_skip_label2(line, i) && line[*i] == LABEL_CHAR && *i <= LABEL_SIZE)
	{
        as_del_label_errors(error, line, *i);
		c = line[*i];
		line[*i] = '\0';
        if (as_cmp_label(*label, line, 0))
        {
			line[*i] = c;
            if (!as_add_error(error, ERROR24, line, 1))
                return (0);
        }
		else if (!as_add_label(label, line, *i, 0))
		{
			line[*i] = c;
			as_free_error(error);
			return (0);
		}
		line[*i] = c;
		(*i)++;
	}
	else if ((*i) > LABEL_SIZE)
	{
        if (!as_add_error(error, ERROR10, line, *i + 1))
            return (0);
		(*i)++;
	}
	else
		*i = 0;
	return (1);
}
