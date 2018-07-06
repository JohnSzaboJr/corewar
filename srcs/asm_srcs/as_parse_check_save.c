/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse_check_save.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/02 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

static int	as_check_quot(int *i, int line_nr, char *line, char *error)
{
	if (!(line[*i]) || line[*i] != '"')
	{
		as_err1(error, line_nr, line, (*i) + 1);
		return (1);
	}
	return (0);
}

int			as_save_comment(int *i, char *line, t_list_byte **code)
{
	int l;

	l = 0;
	while (l < COMMENT_LENGTH && line[*i] != '"')
	{
		if (!(as_add_byte(code, line[*i])))
        	return (0);
		(*i)++;
		l++;
	}
	return (1);
}

int			as_save_name(int *i, char *line, t_list_byte **code)
{
	int l;

	l = 0;
	while (l < PROG_NAME_LENGTH && line[*i] != '"')
	{
		if (!(as_add_byte(code, line[*i])))
        	return (0);
		(*i)++;
		l++;
	}
	return (1);
}

int			as_parse_comment_check(int *i, char *line, int line_nr)
{
	int	j;

	*i = ft_strlen(COMMENT_CMD_STRING);
	j = *i;
	as_skip_space(line, i);
	if (j == *i)
		as_war1(WARNING4, line_nr, line, j + 1);
	as_check_quot(i, line_nr, line, ERROR5);
	as_skip_name(line, i, &j);
	if (!((*i) - j))
		as_war1(WARNING5, line_nr, line, (*i) + 1);
	as_check_quot(i, line_nr, line, ERROR6);
	if (line[*i] && (line[(*i) + 1]))
		as_war1(WARNING6, line_nr, line, (*i) + 2);
	if (((*i) - j) > COMMENT_LENGTH)
		as_war1(WARNING7, line_nr, line, (*i) + 1);
	*i = j;
	return (as_record_error(0)) ? (0) : (1);
}

int			as_parse_name_check(int *i, char *line, int line_nr)
{
	int			j;

	*i = ft_strlen(NAME_CMD_STRING);
	j = *i;
	as_skip_space(line, i);
	if (j == *i)
		as_war1(WARNING1, line_nr, line, j + 1);
	as_check_quot(i, line_nr, line, ERROR2);
	as_skip_name(line, i, &j);
	if (!((*i) - j))
		as_err1(ERROR3, line_nr, line, (*i) + 1);
	as_check_quot(i, line_nr, line, ERROR4);
	if (line[*i] && (line[(*i) + 1]))
		as_war1(WARNING2, line_nr, line, (*i) + 2);
	if (((*i) - j) > PROG_NAME_LENGTH)
		as_war1(WARNING3, line_nr, line, (*i) + 1);
	*i = j;
	return (as_record_error(0)) ? (0) : (1);
}
