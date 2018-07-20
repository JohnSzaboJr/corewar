/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/18 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "as_errors.h"
#include "colors.h"
#include <fcntl.h>

void	as_store_name_comment_init(char *line, int *i, int section, int *length)
{
	*i = (section) ? ft_strlen(COMMENT_CMD_STRING) :
	ft_strlen(NAME_CMD_STRING);
	*length = (section) ? COMMENT_LENGTH : PROG_NAME_LENGTH;
	*i = *i + as_skip_space(line, i) + 1;
}

void	as_store_init(char **l, t_list_byte **c, t_list_byte **s, int *sec)
{
	*l = NULL;
	*c = NULL;
	*s = NULL;
	*sec = 0;
}

int		as_parse_init(char **l, t_list_error **e, int *bc)
{
	*l = NULL;
	*e = NULL;
	*bc = 4;
	return (0);
}

int		as_gparams_init(int *i, t_list_byte **co, char *l, t_list_byte **enc)
{
	int	pos;

	*i = 0;
	as_k(1);
	as_get_pos((*co)->byte, 1);
	pos = as_get_pos(0, 0);
	if (pos != 0 && pos != 8 && pos != 11)
	{
		if (!(as_add_byte(co, 0)))
			return (0);
		*enc = *co;
	}
	else
		*enc = NULL;
	as_skip_to_params(l, i);
	return (1);
}

int		as_pparams_init(int *i, char *line, int *params_size)
{
	int j;
	int	pos;

	*i = 0;
	pos = as_get_pos(0, 0);
	as_k(1);
	*params_size = (pos != 0 && pos != 8 && pos != 11) ? (0) : (1);
	*i = as_skip_label(line, i) + 1;
	as_skip_space(line, i);
	j = as_get_op_pos(line, *i);
	as_get_pos(op_tab[j].opcode, 1);
	as_skip_command(line, i);
	j = *i;
	as_skip_space(line, i);
	if (!line[*i])
		return (0);
	return (*i > j + 1) ? (2) : (1);
}
