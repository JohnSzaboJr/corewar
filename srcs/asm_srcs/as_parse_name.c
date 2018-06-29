/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/26 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

int as_parse_name(char *line, int *section, t_list_num **code)
{
	if (!(ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))))
	{
		int         i;
		int			j;
		t_list_num  *new;

		i = ft_strlen(NAME_CMD_STRING);
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '"')
			i++;
		else
			return (as_error(code, 1));
		j = i;
		while (line[i] && line[i] != '"')
			i++;
		if (!(i - j))
			return (as_error(code, 1));
		ft_printf("value of i - j: %d\n", i - j);

		if ((i - j) > PROG_NAME_LENGTH)
			return (as_error(code, 4));
		if (!(line[i]))
			return (as_error(code, 5));
		// mi van ha nincs idezojel, v egyaltalan nincs ott semmi?
		// mi van ha nincs szokoz a .name utan?
		// tobb idezojeeeel!?
		// hiba ha zaro idexojel utan van valami!
		// error handling: jo-e a hossz meghatarozas? how many bytes?
		i = j;
		while (line[i] != '"')
		{
			if (!(new = (t_list_num *)malloc(sizeof(*new))))
				return (as_error(code, 0));
			new->next = *code;
			*code = new;
			(*code)->num = line[i];
			i++;
		}
		(*section)++;
		return (1);
	}
	return (as_error(code, 1));
}
