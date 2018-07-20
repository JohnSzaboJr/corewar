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
