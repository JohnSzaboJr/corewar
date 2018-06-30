/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse_name_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/30 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

int as_parse_name_check(int *i, char *line, t_list_byte **code, int *length)
{
	int j;
	
	*i = ft_strlen(NAME_CMD_STRING);
	j = *i;
	while (ft_isspace(line[*i]))
		(*i)++;
	if (j == *i || line[*i] != '"')
		return (as_error(code, 1));
	if (line[*i] == '"')
		(*i)++;
	j = *i;
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (!((*i) - j) || !(line[*i]) || (line[(*i) + 1]))
		return (as_error(code, 1));
	*length = ((*i) - j);
	if (*length > PROG_NAME_LENGTH)
		return (as_error(code, 4));
	*i = j;
	return (1);
}
