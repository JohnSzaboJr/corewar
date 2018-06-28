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

void	as_print_list(t_list_num *list)
{
	while (list)
	{
		ft_printf("%x ", list->num);
		list = list->next;
	}
	ft_printf("\n");
}
