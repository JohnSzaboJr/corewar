/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_skip.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/06 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

int as_skip_rev_space(char *line, int *i)
{
    while (ft_isspace(line[*i - 1]))
        (*i)--;
    return (1);
}

int	as_skip_command(char *line, int *i)
{
	while (line[*i] && !ft_isspace(line[*i]))
		(*i)++;
	return (1);
}

int	as_skip_name(char *line, int *i, int *j)
{
	if (line[*i] && line[*i] == '"')
		(*i)++;
	*j = *i;
	while (line[*i] && line[*i] != '"')
		(*i)++;
	return (1);
}

int	as_skip_label(char *line, int *i)
{
	while (line[*i] && ft_strchr(LABEL_CHARS, line[*i]))
		(*i)++;
	return (*i);
}

int	as_skip_space(char *line, int *i)
{
	int	j;

	j = (*i);
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	return ((*i) - j);
}
