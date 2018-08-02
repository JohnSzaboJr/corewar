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
#include "asm_struct.h"
#include "asm_prot.h"
#include "as_errors.h"
#include "colors.h"
#include <fcntl.h>

int	as_type_e(int co, int k, int a)
{
	const int	tab[12] =
	{T_REG, T_REG + T_DIR, T_REG + T_IND, T_REG + T_DIR + T_IND,
	T_DIR, T_REG + T_DIR, T_IND + T_DIR, T_REG + T_DIR + T_IND,
	T_IND, T_REG + T_IND, T_DIR + T_IND, T_REG + T_DIR + T_IND};

	if (k <= op_tab[co].param_count &&
	op_tab[co].param_type[k - 1] != tab[a] &&
	op_tab[co].param_type[k - 1] != tab[a + 1] &&
	op_tab[co].param_type[k - 1] != tab[a + 2] &&
	op_tab[co].param_type[k - 1] != tab[a + 3])
		return (-1);
	return (1);
}

int	as_check_max_length(char *line, t_list_error **error)
{
	if (ft_strlen(line) > MAX_LINE_LENGTH &&
	!as_add_error(error, ERROR17, line, 1))
		return (0);
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