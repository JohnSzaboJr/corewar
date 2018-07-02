/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/01 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

int as_parse_commands(char *line, int line_nr, t_list_byte **code, t_list_label **label)
{
	int				i;
	t_list_label	*new;

	i = 0;
	while (line[i] && ft_strchr(LABEL_CHARS, line[i]))
		i++;
	if (i && line[i] == LABEL_CHAR)
	{
		if (!(new = (t_list_label *)malloc(sizeof(*new))))
			return (as_error(code, 8));
		if (!(new->name = ft_strnew(i)))
			return (as_error(code, 8));
		ft_strncpy(new->name, line, i);
		new->pos = as_code_size(*code);
		new->next = *label;
		*label = new;
		i++;
	}
	else
		i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	as_get_command(line, i, code, line_nr);


	

	// I have to free labels as well!!! (also on errors)
	// parse potential labels (check if there label char)
	// save label name and byte position
	// can label names be the same as known commands?	
	return (1);
}
