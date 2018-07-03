/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_check_after_name.c                              :+:      :+:    :+:   */
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
#include "as_errors.h"
#include <fcntl.h>

int	as_check_after_comment(int *i, int line_nr, char *line)
{
	if (line[*i] && (line[(*i) + 1]))
		as_war1(WARNING6, line_nr, line, (*i) + 2);
	return (1);
}

int	as_check_after_name(int *i, int line_nr, char *line)
{
	if (line[*i] && (line[(*i) + 1]))
		as_war1(WARNING2, line_nr, line, (*i) + 2);
	return (1);
}
