/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/16 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

void		as_errnbr(int n)
{
	char c;

	if (n < 0)
	{
		if (n == -2147483648)
		{
			as_errnbr(-214748364);
			c = '8';
			write(2, &c, 1);
			return ;
		}
		c = '-';
		write(2, &c, 1);
		n *= -1;
	}
	if (n > 9)
		as_errnbr(n / 10);
	c = n % 10 + 48;
	write(2, &c, 1);
}

static void	as_print_error_msg(int t, t_list_error *error)
{
	int lnr;
	int	cnr;

	lnr = error->line_nr;
	cnr = error->column_nr;
	if (t == 1 || t == 6 || t == 7)
		as_err1(error->message, lnr, error->line, cnr);
	if (t == 2)
		as_war1(error->message, lnr, error->line, cnr);
	if (t == 3)
		as_err_note3(lnr, cnr, error->message);
	if (t == 4)
		as_err1(ERROR28, lnr, error->line, cnr);
	if (t == 6)
		as_err_note(lnr, error->line, cnr);
	if (t == 7)
		as_err_note2(lnr, cnr);
	if (t == 5)
		as_err1(error->message, lnr, NULL, 0);
	if (t == 8)
		as_err_note4(lnr, cnr, error->message);
}

static void	as_print_error_loop(t_list_error *error, int *ec, int *wc)
{
	int	t;

	while (error)
	{
		t = error->type;
		(*ec) = (t == 1 || t == 4 || t == 5 || t == 6 || t == 7) ?
		(*ec + 1) : (*ec);
		(*wc) = (t == 2) ? (*wc + 1) : (*wc);
		as_print_error_msg(t, error);
		error = error->next;
	}
}

static void	as_print_error_num(int error_count, int warning_count)
{
	if (!warning_count && !error_count)
		return ;
	ft_putstr_fd("\n", 2);
	if (error_count)
	{
		as_errnbr(error_count);
		ft_putstr_fd(" error", 2);
	}
	if (error_count > 1)
		ft_putstr_fd("s", 2);
	if (error_count && warning_count)
		ft_putstr_fd(" and ", 2);
	if (warning_count)
	{
		as_errnbr(warning_count);
		ft_putstr_fd(" warning", 2);
	}
	if (warning_count > 1)
		ft_putstr_fd("s", 2);
	ft_putstr_fd(" generated.\n", 2);
}

int			as_print_error(t_list_error *error)
{
	int	error_count;
	int	warning_count;

	error_count = 0;
	warning_count = 0;
	as_print_error_loop(error, &error_count, &warning_count);
	as_print_error_num(error_count, warning_count);
	return (error_count);
}
