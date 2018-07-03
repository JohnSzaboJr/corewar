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

int as_save_comment(int *i, char *line, t_list_byte **code, t_list_byte **new)
{
	int l;

	l = 0;
	while (l < COMMENT_LENGTH && line[*i] != '"')
	{
		if (!((*new) = (t_list_byte *)malloc(sizeof(**new))))
		{
			ft_printf(BOLDYELLOW "\nsystem error:" RESET);
			ft_printf(BOLDWHITE ERROR0 RESET);
			ft_printf(WHITE " (as_save_comment)\n" RESET);
			as_free(code);
			return (0);
		}
		(*new)->next = *code;
		*code = *new;
		(*code)->byte = line[*i];
		(*i)++;
		l++;
	}
	return (1);
}

int as_save_name(int *i, char *line, t_list_byte **code, t_list_byte **new)
{
	int l;

	l = 0;
	while (l < PROG_NAME_LENGTH && line[*i] != '"')
	{
		if (!((*new) = (t_list_byte *)malloc(sizeof(**new))))
		{
			ft_printf(BOLDYELLOW "\nsystem error:" RESET);
			ft_printf(BOLDWHITE ERROR0 RESET);
			ft_printf(WHITE " (as_save_name)\n" RESET);
			as_free(code);
			return (0);
		}
		(*new)->next = *code;
		*code = *new;
		(*code)->byte = line[*i];
		(*i)++;
		l++;
	}
	return (1);
}

int as_parse_comment_check(int *i, char *line, t_list_byte **code, int line_nr)
{
	int	j;

	*i = ft_strlen(COMMENT_CMD_STRING);
	j = *i;
	as_skip_space(line, i);
	as_check_comment_space(j, i, line_nr, line);
	as_check_comment_quot1(i, line_nr, line, code);
	as_skip_name(line, i, &j);
	if (!((*i) - j))
		as_war1(WARNING5, line_nr, line, (*i) + 1);
	as_check_comment_quot2(i, line_nr, line, code);
	as_check_after_comment(i, line_nr, line);
	if (((*i) - j) > COMMENT_LENGTH)
		as_war1(WARNING7, line_nr, line, (*i) + 1);
	*i = j;
	return (as_check_error(*code)) ? (0) : (1);
}

int as_parse_name_check(int *i, char *line, t_list_byte **code, int line_nr)
{
	int			j;

	*i = ft_strlen(NAME_CMD_STRING);
	j = *i;
	as_skip_space(line, i);
	as_check_name_space(j, i, line_nr, line);
	as_check_name_quot1(i, line_nr, line, code);
	as_skip_name(line, i, &j);
	if (!((*i) - j))
	{
		as_err1(ERROR3, line_nr, line, (*i) + 1);
		as_record_error(code);
	}
	as_check_name_quot2(i, line_nr, line, code);
	as_check_after_name(i, line_nr, line);
	if (((*i) - j) > PROG_NAME_LENGTH)
		as_war1(WARNING3, line_nr, line, (*i) + 1);
	*i = j;
	return (as_check_error(*code)) ? (0) : (1);
}
