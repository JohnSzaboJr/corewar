/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/05 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

static int as_malloc_error1(t_list_error **error, int a)
{
	//ezeket atirni stderr-re
	ft_printf(BOLDYELLOW "\nsystem error:" RESET);
	ft_printf(BOLDWHITE ERROR0 RESET);
	if (a == 1)
		ft_printf(WHITE " (as_add_error)\n" RESET);
	else if (a == 2)
		ft_printf(WHITE " (as_add_warning)\n" RESET);
	else if (a == 3)
		ft_printf(WHITE " (as_add_note)\n" RESET);
	else if (a == 4)
		ft_printf(WHITE " (as_add_label_error)\n" RESET);
	else if (a == 5)
		ft_printf(WHITE " (as_add_error_noline)\n" RESET);
	else if (a == 6)
		ft_printf(WHITE " (as_add_error_note1)\n" RESET);
	else if (a == 7)
		ft_printf(WHITE " (as_add_error_note2)\n" RESET);
	as_free_error(error);
	return (0);
}

int as_add_error(t_list_error **error, char *message, char *line, int column_nr)
{
	t_list_error	*new;

	if (!(new = (t_list_error *)malloc(sizeof(*new))) ||
	!(new->line = ft_strnew(ft_strlen(line))) ||
	!(new->message = ft_strnew(ft_strlen(message))))
		return (as_malloc_error1(error, 1));
	ft_strcpy(new->line, line);
	ft_strcpy(new->message, message);
	new->type = 1;
	new->line_nr = as_line_nr(0);
	new->column_nr = column_nr;
	new->next = *error;
	*error = new;
	return (1);
}

int as_add_warning(t_list_error **error, char *message, char *line, int column_nr)
{
	t_list_error	*new;

	if (!(new = (t_list_error *)malloc(sizeof(*new))) ||
	!(new->line = ft_strnew(ft_strlen(line))) ||
	!(new->message = ft_strnew(ft_strlen(message))))
		return (as_malloc_error1(error, 2));
	ft_strcpy(new->line, line);
	ft_strcpy(new->message, message);
	new->type = 2;
	new->line_nr = as_line_nr(0);
	new->column_nr = column_nr;
	new->next = *error;
	*error = new;
	return (1);
}

int as_add_note(t_list_error **error, char *message, char *line, int column_nr)
{
	t_list_error	*new;

	if (!(new = (t_list_error *)malloc(sizeof(*new))) ||
	!(new->line = ft_strnew(ft_strlen(line))) ||
	!(new->message = ft_strnew(ft_strlen(message))))
		return (as_malloc_error1(error, 3));
	ft_strcpy(new->line, line);
	ft_strcpy(new->message, message);
	new->type = 3;
	new->line_nr = as_line_nr(0);
	new->column_nr = column_nr;
	new->next = *error;
	*error = new;
	return (1);
}

int as_add_label_error(t_list_error **error, char *message, char *line, int column_nr)
{
	t_list_error	*new;

	if (!(new = (t_list_error *)malloc(sizeof(*new))) ||
	!(new->line = ft_strnew(ft_strlen(line))) ||
	!(new->message = ft_strnew(ft_strlen(message))))
		return (as_malloc_error1(error, 4));
	ft_strcpy(new->line, line);
	ft_strcpy(new->message, message);
	new->type = 4;
	new->line_nr = as_line_nr(0);
	new->column_nr = column_nr;
	new->next = *error;
	*error = new;
	return (1);
}

int as_add_error_noline(t_list_error **error, char *message)
{
	t_list_error	*new;

	if (!(new = (t_list_error *)malloc(sizeof(*new))) ||
	!(new->message = ft_strnew(ft_strlen(message))))
		return (as_malloc_error1(error, 5));
	ft_strcpy(new->message, message);
	new->line = NULL;
	new->type = 5;
	new->line_nr = 0;
	new->column_nr = 0;
	new->next = *error;
	*error = new;
	return (1);
}

int as_add_error_note1(t_list_error **error, char *message, char *line, int column_nr)
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
	new->column_nr = column_nr;
	new->next = *error;
	*error = new;
	return (1);
}

int as_add_error_note2(t_list_error **error, char *message, char *line, int column_nr)
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
	new->column_nr = column_nr;
	new->next = *error;
	*error = new;
	return (1);
}
