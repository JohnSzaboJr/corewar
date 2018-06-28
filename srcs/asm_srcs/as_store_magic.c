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
#include <fcntl.h>

int as_store_magic(t_list_num **code)
{
	t_list_num  *new;

	if (!(new = (t_list_num *)malloc(sizeof(*new))))
	{
		ft_printf("%s\n", "ERROR: couldn't compile due to malloc error in as_store_magic");
		return (0);
	}
	new->next = *code;
	*code = new;
	(*code)->num = COREWAR_EXEC_MAGIC;
	return (1);
}
