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
#include <fcntl.h>

void	as_putnspace(int n)
{
	while (n)
    {
		ft_putchar(' ');
    	n--;
	}
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
