/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_store_magic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/27 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int as_store_magic(t_list_byte **code)
{
	t_list_byte	*new;
	int			magic;
	int			i;

	i = 4;
	magic = COREWAR_EXEC_MAGIC;
	while (i)
	{
		if (!(new = (t_list_byte *)malloc(sizeof(*new))))
		{
			ft_printf(BOLDYELLOW "\nsystem error:" RESET);
			ft_printf(BOLDWHITE ERROR0 RESET);
			ft_printf(WHITE " (as_store_magic)\n" RESET);
			as_free(code);
			return (0);
		}
		new->byte = magic % 256;
		magic = (magic - (magic % (256))) / (256);
		new->next = *code;
		*code = new;
		i--;
	}
	return (1);
}
