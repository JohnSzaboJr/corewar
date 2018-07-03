/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/02 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include <fcntl.h>

void	as_putnspace(int n)
{
	while (n)
    {
		ft_putchar(' ');
    	n--;
	}
}

int		as_err2(char *message, int line_nr, char *line, int column_nr)
{
	int		i;
	int		j;
	int		l;
	char	c;

	i = 0;
	j = 0;
	l = 0;
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDRED " error:" RESET);
	ft_printf(BOLDWHITE "%s" RESET, message);
	ft_printf("%s\n", line);
	j = as_skip_label(line, &i) + 1;
    if (line[i] == LABEL_CHAR)
		l = 1;
	if (line[i] == LABEL_CHAR)
		as_putnspace(i + 1);
	c = line[column_nr - 1];
	line[column_nr - 1] = '\0';
    if (!l)
		j = 0;
	ft_putstr(line + j);
	line[column_nr - 1] = c;
    ft_printf(GREEN "^\n" RESET);
	return (1);
}

int as_war1(char *message, int line_nr, char *line, int column_nr)
{
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDMAGENTA " warning:" RESET);
	ft_printf(BOLDWHITE "%s" RESET, message);
	ft_printf("%s\n", line);
	as_putnspace(column_nr - 1);
	ft_printf(GREEN "^\n" RESET);
	return (1);
}

int		as_err1(char *message, int line_nr, char *line, int column_nr)
{
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDRED " error:" RESET);
	ft_printf(BOLDWHITE "%s" RESET, message);
	ft_printf("%s\n", line);
	as_putnspace(column_nr - 1);
	ft_printf(GREEN "^\n" RESET);
	return (1);
}
