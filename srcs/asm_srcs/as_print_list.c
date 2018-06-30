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
	int i;

	i = 0;
	ft_putstr("output: \n\n");
	while (list)
	{
		if (!(list->byte - (list->byte % 16)))
			ft_putchar('0');
		ft_printf("%x ", list->byte);
		list = list->next;
		i++;
		if (!(i % 8))
			ft_putchar(' ');
		if (!(i % 16))
			ft_putchar('\n');
	}
	ft_printf("\n");
}
