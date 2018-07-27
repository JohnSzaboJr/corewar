/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_store2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/27 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

static int	as_sr(t_list_byte **code, t_list_byte **encoding, char *line)
{
	if (as_enc(encoding, -1) &&
	!(as_add_byte(code, (unsigned char)ft_atoi(line + as_j(0, 0) + 1), 8)))
		return (0);
	return (1);
}

static void	as_bw_sparams(char *line, int *i)
{
	as_skip_space(line, i);
	as_j(1, *i);
	as_skip_to_sep(line, i);
	as_k(2);
}

static void as_putnspace(int n)
{
	while (n)
	{
		ft_putchar(' ');
		n--;
	}
}

static void		as_write_byte(t_list_byte *code)
{
	if (code->byte < 16)
		ft_printf("0");
	ft_printf("%x ", code->byte);
}

// atirni ugy h szetszedni a kodot... (direct - direct)
// majd az as_write_byteot hasznalni a -p nal is

static void		as_print_a1(int n, t_list_byte *code)
{
	if (n == 1)
		ft_printf(CYAN "encoding" RESET);
	if (n == 2)
		ft_printf(MAGENTA "register" RESET);
	as_putnspace(ft_strlen(op_tab[as_get_pos(0, 0)].opname));
	if (n == 1)
		ft_printf(CYAN "   (1 byte):  " RESET);
	if (n == 2)
		ft_printf(MAGENTA "   (1 byte):  " RESET);
	as_write_byte(code);
	ft_putchar('\n');
}

static void		as_print_a2(int n, t_list_byte **op_pos, int *m, char *str)
{
	t_list_byte	*node;
	int			i;
	int			j;
	int			pos;

	i = 0;
	j = 4;
	pos = as_get_pos(0, 0);
	if (((pos == 8 || pos == 9 || pos == 10 || pos == 11) && n == 3) ||
		(pos == 5 && n == 9))
		j = 2;
	node = *op_pos;
	while (*op_pos && (*op_pos)->type == n && *m < j)
	{
		*op_pos = (*op_pos)->next;
		(*m)++;
	}
	if (*m == 1)
		return ;
	ft_printf(MAGENTA "%s" RESET, str);
	as_putnspace(ft_strlen(op_tab[as_get_pos(0, 0)].opname));
	if (n == 3)
		ft_printf("  ");
	ft_printf(MAGENTA "   (%d bytes): " RESET, *m);
	(*op_pos) = node;
	while (i < *m)
	{
		as_write_byte(*op_pos);
		if ((*op_pos)->next)
			node = (*op_pos);
		*op_pos = (*op_pos)->next;
		i++;
	}
	*op_pos = node;
	ft_putchar('\n');
}

static int		as_print_a(t_flags *f, t_list_byte **code, t_list_byte *encoding, t_list_byte **op_pos)
{
	int			m;

	if (f->a && encoding)
		as_print_a1(1, encoding);
	if (f->a)
	{
		as_rlist(code);
		while (*op_pos)
		{
			m = 0;
			if ((*op_pos)->type == 8)
				as_print_a1(2, *op_pos);
			else if ((*op_pos)->type == 3)
				as_print_a2(3, op_pos, &m, "direct");
			else if ((*op_pos)->type == 9)
				as_print_a2(9, op_pos, &m, "indirect");
			if (*op_pos)
				*op_pos = (*op_pos)->next;
		}
		as_rlist(code);
	}
	return (1);
}

int			as_get_params(char *line, t_list_label **label, t_list_byte **code, t_flags *f)
{
	int			i;
	t_list_byte	*encoding;
	t_list_byte	*op_pos;
	int			byte_pos;

	op_pos = *code;
	byte_pos = as_code_size(*code) - 1;
	if (!as_gparams_init(&i, code, line, &encoding))
		return (0);
	while (line[i])
	{
		as_bw_sparams(line, &i);
		if ((((line[as_j(0, 0)] == 'r') && !as_sr(code, &encoding, line))) || 
		((as_dir(line) == 2 && as_enc(&encoding, 2) &&
		!as_dlabel(line, label, byte_pos, code)) ||
		(as_dir(line) == 1 && as_enc(&encoding, 2) && !as_sd(line, code)) ||
		(as_ind(line) == 2 && as_enc(&encoding, 5) &&
		!as_ilabel(line, label, byte_pos, code)) ||
		(as_ind(line) == 1 && as_enc(&encoding, 5) && !as_si(line, code))))
			return (0);
		as_skip_space(line, &i);
		if (line[i])
			i++;
	}
	return (as_print_a(f, code, encoding, &op_pos));
}

int			as_get_command(char *line, int i, t_list_byte **code, t_flags *f)
{
	int	j;
	int	k;

	k = 0;
	j = as_get_op_pos(line, i);
	if (j < 0)
		return (j);
	if (!(as_add_byte(code, (unsigned char)op_tab[j].opcode, 1)))
		return (0);
	if (f->a)
	{
		ft_printf(GREEN "operation %s (1 byte):  " RESET, op_tab[j].opname);
		if ((*code)->byte < 16)
			ft_printf("0");
		ft_printf("%x\n", (*code)->byte);
	}
	return (1);
}
