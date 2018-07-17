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

int as_add_label_note(t_list_error **error, char *message, int column_nr)
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
	new->column_nr = column_nr;
	new->next = *error;
	*error = new;
	return (1);
}

static void	as_putspace(char *line, int i)
{
	char	c;

	c = (ft_isspace(line[i])) ? (line[i]) : (' ');
	write(2, &c, 1);
}

static void	as_err_line_dots(char *line)
{
	char	c;

	c = line[MAX_ERROR_SIZE - 1];
	line[MAX_ERROR_SIZE - 1] = '\0';
	ft_putstr_fd(line, 2);
	ft_putstr_fd("...\n", 2);
	line[MAX_ERROR_SIZE - 1] = c;
}

void	as_write_err(char *message, int line_nr, int column_nr, int e)
{
	if (column_nr)
	{
		ft_putstr_fd(BOLDWHITE, 2);
		ft_putstr_fd("\nline ", 2);
		as_errnbr(line_nr);
		ft_putstr_fd(", column ", 2);
		as_errnbr(column_nr);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(RESET, 2);
	}
    if (e)
		ft_putstr_fd(BOLDRED "error:" RESET, 2);
    else
		ft_putstr_fd(BOLDMAGENTA "warning:" RESET, 2);
	ft_putstr_fd(BOLDWHITE, 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(RESET, 2);
}

static void	as_write_long_err(char *line, int column_nr)
{
	char c;

	c = line[MAX_ERROR_SIZE + column_nr - 6];
	line[MAX_ERROR_SIZE + column_nr - 6] = '\0';
	ft_putstr_fd(line + column_nr - 5, 2);
	ft_putstr_fd("...\n", 2);
	line[MAX_ERROR_SIZE + column_nr - 6] = c;	
}

void    as_write_err_line(char *line, int column_nr)
{
    if (ft_strlen(line) > MAX_ERROR_SIZE && column_nr < MAX_ERROR_SIZE)
		as_err_line_dots(line);
	else if (ft_strlen(line) > MAX_ERROR_SIZE && column_nr >= MAX_ERROR_SIZE)
	{
		ft_putstr_fd("...", 2);
		if (ft_strlen(line + column_nr - 5) > MAX_ERROR_SIZE)
			as_write_long_err(line, column_nr);
		else
		{
			ft_putstr_fd(line + column_nr - 5, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	else
	{
		ft_putstr_fd(line, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	as_write_err_sign(char *line, int column_nr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strlen(line) > MAX_ERROR_SIZE && column_nr >= MAX_ERROR_SIZE)
	{
		i = column_nr - 5;
		while (j < 7)
		{
			as_putspace(line, i);
			i++;
			j++;
		}
	}
	else
	{
		while (i < column_nr - 1)
		{
			as_putspace(line, i);
			i++;
		}
	}
	ft_putstr_fd(GREEN "^\n" RESET, 2);
}
