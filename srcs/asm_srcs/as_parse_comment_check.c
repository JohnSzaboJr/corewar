/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse_comment_check.c                           :+:      :+:    :+:   */
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

int as_parse_comment_check(int *i, char *line, t_list_byte **code, int *length)
{
	int j;
	
	*i = ft_strlen(COMMENT_CMD_STRING);
	j = *i;
	while (ft_isspace(line[*i]))
		(*i)++;
	if (j == *i || line[*i] != '"')
		return (as_error(code, 3));
	if (line[*i] == '"')
		(*i)++;
	j = *i;
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (!((*i) - j) || !(line[*i]) || (line[(*i) + 1]))
		return (as_error(code, 3));
	*length = ((*i) - j);
	if (*length > COMMENT_LENGTH)
		return (as_error(code, 6));
	*i = j;
	return (1);
}
