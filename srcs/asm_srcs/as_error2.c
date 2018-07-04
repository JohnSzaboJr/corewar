/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/04 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

static void	as_putspace(char *line, int i)
{
	if (ft_isspace(line[i]))
		ft_putchar(line[i]);
	else
		ft_putchar(' ');
}

static void	as_err_line_dots(char *line)
{
	char	c;

	c = line[MAX_ERROR_SIZE - 1];
	line[MAX_ERROR_SIZE - 1] = '\0';
	ft_printf("%s", line);
	ft_printf("...\n");
	line[MAX_ERROR_SIZE - 1] = c;
}

void	as_write_err(char *message, int line_nr, int column_nr, int e)
{
    ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
    if (e)
	    ft_printf(BOLDRED " error:" RESET);
    else
        ft_printf(BOLDMAGENTA " warning:" RESET);
	ft_printf(BOLDWHITE "%s" RESET, message);
}

void    as_write_err_line(char *line, int column_nr)
{
    char    c;
	int		l;

	l = ft_strlen(line);
    if (l > MAX_ERROR_SIZE && column_nr < MAX_ERROR_SIZE)
		as_err_line_dots(line);
	else if (l > MAX_ERROR_SIZE && column_nr >= MAX_ERROR_SIZE)
	{
		ft_printf("...");
		if (ft_strlen(line + column_nr - 5) > MAX_ERROR_SIZE)
		{
			c = line[MAX_ERROR_SIZE + column_nr - 6];
			line[MAX_ERROR_SIZE + column_nr - 6] = '\0';
			ft_printf("%s", line + column_nr - 5);
			ft_printf("...\n");
			line[MAX_ERROR_SIZE + column_nr - 6] = c;
		}
		else
			ft_printf("%s\n", line + column_nr - 5);
	}
	else
		ft_printf("%s\n", line);
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
	ft_printf(GREEN "^\n" RESET);
}
