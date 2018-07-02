/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_store_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/02 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "as_errors.h"
#include "colors.h"
#include <fcntl.h>

int as_store_error(t_list_byte **code)
{
	t_list_byte	*new;

	if (!(new = (t_list_byte *)malloc(sizeof(*new))))
	{
		ft_printf(BOLDYELLOW "\nsystem error:" RESET);
		ft_printf(BOLDWHITE ERROR0 RESET);
		ft_printf(WHITE " (as_store_error)\n" RESET);
		as_free(code);
		return (0);
	}
	new->byte = 0;
	new->next = *code;
	*code = new;
	as_reverse_list(code);
	return (1);
}
