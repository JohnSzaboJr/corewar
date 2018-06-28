/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_reverse_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/28 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

int	as_reverse_list(t_list_num **list)
{
	t_list_num *next;
	t_list_num *tmp;
	t_list_num *node;

	next = NULL;
	tmp = NULL;
	node = *list;
	while (node && node->next)
		node = node->next;
	while (*list)
	{
		next = (*list)->next;
		(*list)->next = tmp;
		tmp = *list;
		*list = next;
	}
	*list = node;
	return (1);
}
