/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/03 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "as_errors.h"
#include "colors.h"
#include <fcntl.h>

int as_close(int fd, char *filename)
{
	if (close(fd) < 0)
		return (as_err2(ERROR34, filename));		
	return (1);
}

void	as_write_bytes(t_list_byte **code, int info, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		(*code)->byte = (info >> (8 * i)) & 0xff;
		(*code) = (*code)->next;
		i++;
	}
}

int		as_add_bytes(t_list_byte **code, int n)
{
	while (n)
	{
		if (!as_add_byte(code, 0))
			return (0);
		n--;
	}
	return (1);
}

int		as_add_byte(t_list_byte **code, unsigned char byte)
{
	t_list_byte	*new;

	if (!(new = (t_list_byte *)malloc(sizeof(*new))))
	{
		ft_printf(BOLDYELLOW "\nsystem error:" RESET);
		ft_printf(BOLDWHITE ERROR0 RESET);
		ft_printf(WHITE " (as_add_byte)\n" RESET);
		as_free(code);
		return (0);
	}
	new->next = *code;
	*code = new;
	(*code)->byte = byte;
	return (1);
}

int		as_add_label(t_list_label **label, char *line, int i, int pos)
{
	t_list_label	*new;

	if (!(new = (t_list_label *)malloc(sizeof(*new))))
	{
		ft_printf(BOLDYELLOW "\nsystem error:" RESET);
		ft_printf(BOLDWHITE ERROR0 RESET);
		ft_printf(WHITE " (as_add_label)\n" RESET);
		as_free_label(label);
		return (0);
	}
	new->next = *label;
	*label = new;
	if (!((*label)->name = ft_strnew(i)))
	{
		ft_printf(BOLDYELLOW "\nsystem error:" RESET);
		ft_printf(BOLDWHITE ERROR0 RESET);
		ft_printf(WHITE " (as_add_label)\n" RESET);
		as_free_label(label);
		return (0);
	}
	ft_strncpy((*label)->name, line, i);
	(*label)->pos = pos;
	return (1);
}

int as_code_size(t_list_byte *code)
{
	int i;

	i = 0;
	while (code)
	{
		code = code->next;
		i++;
	}
	return (i);
}

int	as_cmd_comp(char *cmd, char *str)
{
	int	i;
	int	j;
	int	k;
	int	ret;

	ret = 0;
	j = 0;
	k = 0;
	while ((j < 5 && str[j] && !ft_isspace(str[j]) && str[j] != cmd[k]) ||
	(str[j] && str[j + 1] && str[j + 1] == cmd[k]))
		j++;
	i = ft_strlen(cmd);
	while (i && str[j] && !ft_isspace(str[j]))
	{
		if (cmd[k] == str[j])
			ret++;
		else if (k > 1)
			k--;
		j++;
		k++;
		i--;
	}
	return (ret);
}

int	as_reverse_list(t_list_byte **list)
{
	t_list_byte *next;
	t_list_byte *tmp;
	t_list_byte *node;

	next = NULL;
	tmp = NULL;
	node = *list;
	while (node && node->next)
		node = node->next;
	while (*list)
	{
		next = (*list)->next;
		(*list)->next = tmp;
		tmp = *list;
		*list = next;
	}
	*list = node;
	return (1);
}

int	as_reverse_error(t_list_error **list)
{
	t_list_error *next;
	t_list_error *tmp;
	t_list_error *node;

	next = NULL;
	tmp = NULL;
	node = *list;
	while (node && node->next)
		node = node->next;
	while (*list)
	{
		next = (*list)->next;
		(*list)->next = tmp;
		tmp = *list;
		*list = next;
	}
	*list = node;
	return (1);
}
