/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/20 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <unistd.h>

static void	as_dlnode(t_list_error **node, t_list_error **error)
{
	free((*node)->message);
    free((*node)->line);
    free(*node);
    *node = *error;
    *error = (*error)->next;
}

void as_del_label_errors(t_list_error **error, char *line, int i)
{
    t_list_error    *node;
    t_list_error    *prev;

    node = *error;
    (*error) = (*error)->next;
    while (node->type == 4 && !ft_strncmp(node->message, line, i))
		as_dlnode(&node, error);
    prev = node;
    while (*error)
    {
        if ((*error)->type == 4 && !ft_strncmp((*error)->message, line, i))
        {
            free((*error)->message);
            free((*error)->line);
            prev->next = (*error)->next;
            free(*error);
            *error = prev;
        }
        prev = *error;
        *error = (*error)->next;
    }
    *error = node;
}

char *as_label_sug(char *str, t_list_label *label)
{
	int             highest;
	t_list_label    *pos;
	int             save;

	highest = 0;
    while (label)
    {
        if ((save = as_cmd_comp(label->name, str)) > highest)
		{
			pos = label;
			highest = save;
		}
        label = label->next;
    }
	if (highest > 1)
        return (pos->name);
    else
        return (NULL);
}
