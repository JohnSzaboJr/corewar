/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error_check3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/20 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "as_errors.h"
#include "colors.h"
#include <fcntl.h>

int	as_check_max_length(char *line, t_list_error **error)
{
	if (ft_strlen(line) > MAX_LINE_LENGTH &&
	!as_add_error(error, ERROR17, line, 1))
        return (0);
	return (1);
}

int  as_r_e(char *line, int *i, t_list_error **error, int *params_size)
{
    int j;
    int ret;
	int	pos;

	pos = as_get_pos(0, 0);
    ret = 0;
    j = as_j(0, 0) + 1;
    if (!line[j] || ft_isspace(line[j]) || line[j] == SEPARATOR_CHAR)
    {
        ret = -1;
        if (!as_add_error(error, ERROR12, line, j + 1))
            return (0);
    }
    else if (line[j])
    {
        if (!(ret = as_check_r(line, i, j - 1, error)) ||
		(((ret = as_type_e(pos, as_k(0), 0)) == -1) &&
		(!as_add_error(error, ERROR15, line, j) ||
		!as_add_note_type(error, as_get_err_par(pos, as_k(0)), line, j))))
			return (0);
    }
    if (ret != -1)
        (*params_size)++;
    return (1);
}

int  as_d_e(char *line, int *i, t_list_error **error, int *ps)
{
    int j;
    int ret;
	int	pos;

    ret = 0;
	pos = as_get_pos(0, 0);
    j = as_j(0, 0) + 1;
    if (!line[j] || ft_isspace(line[j]) || line[j] == SEPARATOR_CHAR)
    {
        ret = -1;
        if (!as_add_error(error, ERROR25, line, j + 1))
            return (0);
    }
    else if (line[j])
    {
        if (!(ret = as_check_dir(line, i, j - 1, error)))
            return (0);
        if ((-1 == (ret = as_type_e(pos, as_k(0), 4))) &&
		(!as_add_error(error, ERROR15, line, j) ||
		!as_add_note_type(error, as_get_err_par(pos, as_k(0)), line, j)))
            return (0);
    }
	*ps = (ret != -1) ? (*ps + DIR_SIZE) : (*ps);
	*ps = (ret != -1 && pos == 10) ? (*ps - DIR_SIZE + IND_SIZE) : (*ps);
    return (1);
} 

int  as_i_e(char *line, int *i, t_list_error **error, int *params_size)
{
    int j;
    int ret;
	int	pos;

    ret = 0;
	pos = as_get_pos(0, 0);
    j = as_j(0, 0);
    if (!(ret = as_check_ind(line, i, j, error)))
        return (0);
    if (ret != -1 && (-1 == (ret = as_type_e(pos, as_k(0), 8))))
    {
        if (!as_add_error(error, ERROR15, line, j + 1))
            return (0);
        if (!as_add_note_type(error, as_get_err_par(pos, as_k(0)), line, j + 1))
            return (0);
    }
    if (ret != -1)
        *params_size = *params_size + IND_SIZE;
    return (1);
}
