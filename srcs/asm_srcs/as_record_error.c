/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_record_error.c                                  :+:      :+:    :+:   */
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
#include <fcntl.h>

int	as_record_error(t_list_byte **code)
{
	t_list_byte	*node;
	static int	i = 0;

	node = *code;
	while ((*code)->next)
		*code = (*code)->next;
	(*code)->byte = 'Y';
	*code = node;
	i++;
	return (i);
}
