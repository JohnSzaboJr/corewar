/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_print_list.c                                    :+:      :+:    :+:   */
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

void	as_print_list(t_list_byte *list)
{
	int			i;
	int			j;
	int			k;
	int			l;
	int			beg;
	t_list_byte *node;

	i = 0;
	j = 0;
	k = 0;
	l = 1;
	beg = 1;
	ft_putstr("output: \n\n");
	while (list)
	{
		node = list;
		while (list && beg && list->byte == 0 && j < 16)
		{
			j++;
			list = list->next;
		}
		beg = 0;
		if (k && j == 16)
		{
			if (l)
			{
				ft_printf("*\n");
				l = 0;
			}
		}
		else
		{
			list = node;
			if (!(list->byte - (list->byte % 16)))
				ft_putchar('0');
			ft_printf("%x ", list->byte);
			list = list->next;
			i++;
			if (!(i % 8))
				ft_putchar(' ');
			if (!(i % 16))
				ft_putchar('\n');
			k = (k & l) ? 1 : 0;
			l = 1;
		}
		if (!(i % 16))
			beg = 1;
		else
			beg  = 0;
		if (j == 16)
			k = 1;
		j = 0;
	}
	ft_printf("\n");
}
