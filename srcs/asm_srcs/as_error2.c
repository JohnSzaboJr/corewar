/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/17 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <unistd.h>

int as_add_error_note1(t_list_error **error, char *message, char *line, int cnr)
{
	t_list_error	*new;

	if (!(new = (t_list_error *)malloc(sizeof(*new))) ||
	!(new->line = ft_strnew(ft_strlen(line))) ||
	!(new->message = ft_strnew(ft_strlen(message))))
		return (as_malloc_error1(error, 6));
	ft_strcpy(new->line, line);
	ft_strcpy(new->message, message);
	new->type = 6;
	new->line_nr = as_line_nr(0);
	new->column_nr = cnr;
	new->next = *error;
	*error = new;
	return (1);
}

int as_add_error_note2(t_list_error **error, char *message, char *line, int cnr)
{
	t_list_error	*new;

	if (!(new = (t_list_error *)malloc(sizeof(*new))) ||
	!(new->line = ft_strnew(ft_strlen(line))) ||
	!(new->message = ft_strnew(ft_strlen(message))))
		return (as_malloc_error1(error, 7));
	ft_strcpy(new->line, line);
	ft_strcpy(new->message, message);
	new->type = 7;
	new->line_nr = as_line_nr(0);
	new->column_nr = cnr;
	new->next = *error;
	*error = new;
	return (1);
}

int as_add_label_note(t_list_error **error, char *message, int cnr)
{
	t_list_error	*new;

	if (!(new = (t_list_error *)malloc(sizeof(*new))))
		return (as_malloc_error1(error, 8));
	if (!(new->message = ft_strnew(ft_strlen(message))))
		return (as_malloc_error1(error, 8));
	ft_strcpy(new->message, message);
	new->line = NULL;
	new->type = 8;
	new->line_nr = as_line_nr(0);
	new->column_nr = cnr;
	new->next = *error;
	*error = new;
	return (1);
}

int as_add_note_msg(t_list_error **error, char *message, int cnr)
{
	t_list_error	*new;

	if (!(new = (t_list_error *)malloc(sizeof(*new))) ||
	!(new->message = ft_strnew(ft_strlen(message))))
		return (as_malloc_error1(error, 9));
	ft_strcpy(new->message, message);
	new->line = NULL;
	new->type = 9;
	new->line_nr = as_line_nr(0);
	new->column_nr = cnr;
	new->next = *error;
	*error = new;
	return (1);
}
