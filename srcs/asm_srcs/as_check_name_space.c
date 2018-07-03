/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_check_name_space.c                              :+:      :+:    :+:   */
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

int	as_check_comment_space(int j, int *i, int line_nr, char *line)
{
	if (j == *i)
		as_war1(WARNING4, line_nr, line, j + 1);
	return (1);
}

int	as_check_name_space(int j, int *i, int line_nr, char *line)
{
	if (j == *i)
		as_war1(WARNING1, line_nr, line, j + 1);
	return (1);
}
