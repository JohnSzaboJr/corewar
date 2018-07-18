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

int	as_check_valid_params(t_list_error **error, char *line)
{
	return (line[as_j(0, 0)] != 'r' && !as_dir(line) && !as_ind(line) &&
	!as_add_error(error, ERROR11, line, as_j(0, 0) + 1)) ? (0) : (1);
}
