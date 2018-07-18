/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/12 14:35:38 by jszabo           ###   ########.fr       */
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

void as_store_init(char **l, t_list_byte **c, t_list_byte **s, int *sec)
{
	*l = NULL;
	*c = NULL;
	*s = NULL;
	*sec = 0;
}

int	as_parse_init(char **l, t_list_error **e, int *bc)
{
	*l = NULL;
	*e = NULL;
	*bc = 4;
	return (0);
}