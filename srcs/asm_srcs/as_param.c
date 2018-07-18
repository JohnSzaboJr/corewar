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
