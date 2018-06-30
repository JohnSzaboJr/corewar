/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/03/23 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"

int	as_free(t_list_byte **list)
{
	t_list_byte *tmp;

	while (*list)
	{
		tmp = *list;
		free(*list);
		*list = tmp->next;
	}
	return (1);
}
