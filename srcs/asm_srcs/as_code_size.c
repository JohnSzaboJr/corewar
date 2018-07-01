/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_code_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/01 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

int as_code_size(t_list_byte *code)
{
	int i;

	i = 0;
	while (code)
	{
		code = code->next;
		i++;
	}
	return (i);
}
