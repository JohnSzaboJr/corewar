/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error_check2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/08/02 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm_struct.h"
#include "asm_prot.h"
#include "as_errors.h"
#include "colors.h"
#include <fcntl.h>

static int	as_check_quot(int *i, t_list_error **err, char *line, char *message)
{
	if (line[*i] != '"')
	{
		if (!as_add_error(err, message, line, (*i) + 1))
			return (0);
	}
	else
	{
		as_endcomment(line, 1);
		return (2);
	}
	return (1);
}

static void	as_ccheck_init(int *bc, int *i, int *j, char *line)
{
	*bc = (*bc) + COMMENT_LENGTH + 8;
	*i = ft_strlen(COMMENT_CMD_STRING);
	*j = *i;
	as_skip_space(line, i);	
}

static void	as_ncheck_init(int *bc, int *i, int *j, char *line)
{
	*bc = (*bc) + PROG_NAME_LENGTH + 4;
	*i = ft_strlen(NAME_CMD_STRING);
	*j = *i;
	as_skip_space(line, i);
}

static int	as_set_nline_c(int *i, t_list_error **error, char *line, int *comment)
{
	int	ret;

	ret = as_check_quot(i, error, line, ERROR5);
	if (!ret)
		return (0);
	else if (ret == 2)
		*comment = 1;
	return (1);
}

static int	as_set_nline_n(int *i, t_list_error **error, char *line, int *comment)
{
	int	ret;

	ret = as_check_quot(i, error, line, ERROR2);
	if (!ret)
		return (0);
	else if (ret == 2)
		*comment = 1;
	return (1);
}

static int	as_ccheck1(char *line, int *i, int *j, t_list_error **error)
{
	if (!as_skip_name(line, i, j))
	{
		if (!as_add_error(error, ERROR17, line, *j + 1))
			return (0);
		return (2);
	}
	if ((!((*i) - *j) && line[*i] == '"' && !as_add_warning(error, WARNING5, line, (*i) + 1)))
		return (0);
	if (!((*i) - *j) && line[*i] == '"')
		return (2);
	return (1);
}

static int	as_ncheck1(char *line, int *i, int *j, t_list_error **error)
{
	if (!as_skip_name(line, i, j))
	{
		if (!as_add_error(error, ERROR17, line, *j + 1))
			return (0);
		return (2);
	}
	if ((!((*i) - *j) && line[*i] == '"' && !as_add_error(error, ERROR3, line, (*i) + 1)))
		return (0);
	if (!((*i) - *j) && line[*i] == '"')
		return (2);
	return (1);
}

static int	as_clength_e(int length, t_list_error **error, char *line, int *i)
{
	if (((length > COMMENT_LENGTH) &&
	!as_add_warning(error, WARNING7, line, (*i) + 2)))
		return (0);
	if (line[*i + 1] && !as_add_warning(error, WARNING6, line, (*i) + 1))
		return (0);
	return (2);
}

static int	as_nlength_e(int length, t_list_error **error, char *line, int *i)
{
	if (((length > COMMENT_LENGTH) &&
	!as_add_warning(error, WARNING3, line, (*i) + 2)))
		return (0);
	if (line[*i + 1] && !as_add_warning(error, WARNING2, line, (*i) + 1))
		return (0);
	return (2);
}

static int	as_ccheck_init2(char *line, int *i, int *j, t_list_error **error)
{
	as_endcomment(line, 1);
	*i = 0;
	if (!as_skip_name(line, i, j))
	{
		if (!as_add_error(error, ERROR17, line, *j + 1))
			return (0);
		return (2);
	}
	return (1);
}

static int	as_c_end(int length, t_list_error **error, char *line, int *i)
{
	if ((length > COMMENT_LENGTH) &&
	!as_add_warning(error, WARNING7, line, (*i) + 2))
		return (0);
	if (line[*i] && line[*i] == '"' && line[*i + 1] &&
	!as_add_warning(error, WARNING6, line, (*i) + 2))
		return (0);
	if (line[*i] && line[*i] == '"')
		return (2);
	return (1);
}

static int	as_n_end(int length, t_list_error **error, char *line, int *i)
{
	if ((length > COMMENT_LENGTH) &&
	!as_add_warning(error, WARNING3, line, (*i) + 2))
		return (0);
	if (line[*i] && line[*i] == '"' && line[*i + 1] &&
	!as_add_warning(error, WARNING2, line, (*i) + 2))
		return (0);
	if (line[*i] && line[*i] == '"')
		return (2);
	return (1);
}

int			as_comment_check(int *i, char *line, t_list_error **error, int *bc)
{
	int			j;
	static int	comment = 0;
	static int	length = 0;
	int			ret;

	if (!comment)
	{
		as_ccheck_init(bc, i, &j, line);
		if (((j == *i && !as_add_warning(error, WARNING4, line, j + 1))) ||
		!as_set_nline_c(i, error, line, &comment))
			return (0);
		if ((ret = as_ccheck1(line, i, &j, error)) != 1)
			return (ret);
		length = (*i) - j;
		if (((*i) - j) && line[*i] == '"')
			return (as_clength_e(length, error, line, i));
	}
	else
	{
		if ((ret = as_ccheck_init2(line, i, &j, error)) != 1)
			return (ret);
		length = length + (*i) - j + 1;
		return (as_c_end(length, error, line, i));
	}
	return (1);
}

int			as_name_check(int *i, char *line, t_list_error **error, int *bc)
{
	int			j;
	static int	name = 0;
	static int	length = 0;
	int			ret;

	if (!name)
	{
		as_ncheck_init(bc, i, &j, line);
		if (((j == *i && !as_add_warning(error, WARNING1, line, j + 1))) ||
		!as_set_nline_n(i, error, line, &name))
			return (0);
		if ((ret = as_ncheck1(line, i, &j, error)) != 1)
			return (ret);
		length = (*i) - j;
		if (((*i) - j) && line[*i] == '"')
			return (as_nlength_e(length, error, line, i));
	}
	else
	{
		if ((ret = as_ccheck_init2(line, i, &j, error)) != 1)
			return (ret);
		length = length + (*i) - j + 1;
		return (as_n_end(length, error, line, i));
	}
	return (1);
}

int	as_check_valid_params(t_list_error **error, char *line)
{
	return (line[as_j(0, 0)] != 'r' && !as_dir(line) && !as_ind(line) &&
	!as_add_error(error, ERROR11, line, as_j(0, 0) + 1)) ? (0) : (1);
}

int	as_check_spaces_line(char *line, t_list_error **error)
{
	int	i;

	i = 0;
	if (as_skip_space(line, &i) == (int)ft_strlen(line))
    {
        if (!as_endcomment(line, 2) && !as_add_warning2(error, WARNING16, line, i + 1))
            return (-1);
        return (1);
    }
	return (0);
}
