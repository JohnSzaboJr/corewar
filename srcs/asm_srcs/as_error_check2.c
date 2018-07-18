/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error_check2.c                                  :+:      :+:    :+:   */
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
#include "as_errors.h"
#include "colors.h"
#include <fcntl.h>

static int	as_check_quot(int *i, t_list_error **err, char *line, char *message)
{
	if ((!(line[*i]) || line[*i] != '"') &&
	!as_add_error(err, message, line, (*i) + 1))
		return (0);
	return (1);
}

int			as_parse_comment_check(int *i, char *line, t_list_error **error)
{
	int	j;

	*i = ft_strlen(COMMENT_CMD_STRING);
	j = *i;
	as_skip_space(line, i);
	if ((j == *i && !as_add_warning(error, WARNING4, line, j + 1)) ||
	!as_check_quot(i, error, line, ERROR5))
		return (0);
	as_skip_name(line, i, &j);
	if ((!((*i) - j) && !as_add_warning(error, WARNING5, line, (*i) + 1)) ||
	!as_check_quot(i, error, line, ERROR6) ||
	((line[*i] && (line[(*i) + 1])) &&
	!as_add_warning(error, WARNING6, line, (*i) + 2)) ||
	((((*i) - j) > PROG_NAME_LENGTH) &&
	!as_add_warning(error, WARNING7, line, (*i) + 1)))
		return (0);
	*i = j;
	return (1);
}

int			as_parse_name_check(int *i, char *line, t_list_error **error)
{
	int			j;

	*i = ft_strlen(NAME_CMD_STRING);
	j = *i;
	as_skip_space(line, i);
	if ((j == *i && !as_add_warning(error, WARNING1, line, j + 1)) ||
	!as_check_quot(i, error, line, ERROR2))
		return (0);
	as_skip_name(line, i, &j);
	if ((!((*i) - j) && !as_add_error(error, ERROR3, line, (*i) + 1)) ||
	!as_check_quot(i, error, line, ERROR4) ||
	((line[*i] && (line[(*i) + 1])) &&
	!as_add_warning(error, WARNING2, line, (*i) + 2)) ||
	((((*i) - j) > PROG_NAME_LENGTH) &&
	!as_add_warning(error, WARNING3, line, (*i) + 1)))
		return (0);
	*i = j;
	return (1);
}

int	as_check_valid_params(t_list_error **error, char *line)
{
	return (line[as_j(0, 0)] != 'r' && !as_dir(line) && !as_ind(line) &&
	!as_add_error(error, ERROR11, line, as_j(0, 0) + 1)) ? (0) : (1);
}
