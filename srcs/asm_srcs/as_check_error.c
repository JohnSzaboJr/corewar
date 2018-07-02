/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_check_error.c                                   :+:      :+:    :+:   */
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
#include "colors.h"
#include <fcntl.h>

int as_check_error(t_list_byte *code)
{
	while (code->next)
		code = code->next;
	if (code->byte == 'Y')
		return (1);
	return (0);
}
