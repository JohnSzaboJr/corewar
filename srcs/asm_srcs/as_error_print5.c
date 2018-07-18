/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error_print5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/18 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

void	as_label_error(char *message, int lnr, char *line, int cnr)
{
	as_err1(ERROR28, lnr, line, cnr);
	if (message)
		as_note_label(lnr, cnr, message);
}
