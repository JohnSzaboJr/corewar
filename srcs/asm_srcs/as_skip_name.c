/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_skip_name.c                                     :+:      :+:    :+:   */
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

int	as_skip_name(char *line, int *i, int *j)
{
	if (line[*i] && line[*i] == '"')
		(*i)++;
	*j = *i;
	while (line[*i] && line[*i] != '"')
		(*i)++;
	return (1);
}
