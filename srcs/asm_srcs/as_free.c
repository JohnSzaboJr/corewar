/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/03/23 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"

int	as_free_error(t_list_error **list)
{
	t_list_label	*tmp;

	while (*list)
	{
		tmp = *list;
		if ((*list)->line)
			free((*list)->line);
		if ((*list)->message)
			free((*list)->message);
		free(*list);
		*list = tmp->next;
	}
	return (1);
}

int	as_free_label(t_list_label **list)
{
	t_list_label	*tmp;

	while (*list)
	{
		tmp = *list;
		if ((*list)->name)
			free((*list)->name);
		free(*list);
		*list = tmp->next;
	}
	return (1);
}

int	as_free(t_list_byte **list)
{
	t_list_byte *tmp;

	while (*list)
	{
		tmp = *list;
		free(*list);
		*list = tmp->next;
	}
	return (1);
}
