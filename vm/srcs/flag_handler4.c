/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handler4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 18:04:49 by jszabo            #+#    #+#             */
/*   Updated: 2018/08/18 18:04:49 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	update_prev(t_vm *vm, int no, int i)
{
	t_champ *tmp;

	if (no != 0)
	{
		tmp = vm->champs;
		while (tmp)
		{
			if (tmp->number == -no)
				tmp->number = i;
			tmp = tmp->next;
		}
	}
}

int			determine_no(t_vm *vm, int no)
{
	int		i;
	t_champ	*tmp;
	int		changed;

	i = 1;
	changed = 0;
	tmp = vm->champs;
	while (tmp)
	{
		changed = 0;
		if (tmp->number == i || tmp->number == -i)
		{
			changed = 1;
			i++;
			if (i > MAX_PLAYERS)
				i = 1;
		}
		tmp = (changed) ? vm->champs : tmp->next;
	}
	update_prev(vm, no, i);
	return (no == 0) ? (i) : (no);
}
