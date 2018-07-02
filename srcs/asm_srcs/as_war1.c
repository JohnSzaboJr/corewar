/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_war1.c                                          :+:      :+:    :+:   */
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

int as_war1(char *message, int line_nr, char *line, int column_nr)
{
	ft_printf(BOLDWHITE "\nline %d, column %d:" RESET, line_nr, column_nr);
	ft_printf(BOLDMAGENTA " warning:" RESET);
	ft_printf(BOLDWHITE "%s" RESET, message);
	ft_printf("%s\n", line);
	column_nr--;
	while (column_nr)
    {
    	ft_putchar(' ');
    	column_nr--;
    }
	ft_printf(GREEN "^\n" RESET);
	return (1);
}
