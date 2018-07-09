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
	if (a == 2)
		ft_printf(WHITE " (as_add_warning)\n" RESET);
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
		return (as_malloc_error1(error, 2));
	ft_strcpy(new->line, line);
	ft_strcpy(new->message, message);
	new->type = 3;
	new->line_nr = as_line_nr(0);
	new->column_nr = column_nr;
	new->next = *error;
	*error = new;
	return (1);
}

int	as_err1(char *message, int line_nr, char *line, int column_nr)
{
	as_record_error(1);
	as_write_err(message, line_nr, column_nr, 1);
	as_write_err_line(line, column_nr);
	as_write_err_sign(line, column_nr);
	if (message[1] == 'u')
		as_err_note(line_nr, line, column_nr);
	return (1);
}

int as_war1(char *message, int line_nr, char *line, int column_nr)
{
	as_write_err(message, line_nr, column_nr, 0);
	as_write_err_line(line, column_nr);
	as_write_err_sign(line, column_nr);
	return (1);
}

int	as_record_error(int a)
{
	static int	i = 0;

	if (a)
		i++;
	return (i);
}