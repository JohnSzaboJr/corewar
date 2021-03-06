/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 19:33:55 by yabdulha          #+#    #+#             */
/*   Updated: 2018/08/22 00:06:05 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		load_processes(t_vm *vm)
{
	int		i;
	int		j;
	int		k;
	t_champ	*tmp;

	tmp = vm->champs;
	i = 0;
	j = 0;
	while (tmp)
	{
		tmp->reg[0] = tmp->number < 0 ? -(tmp->number) : tmp->number;
		tmp->number = tmp->number < 0 ? -(tmp->number) : tmp->number;
		i = (MEM_SIZE / (vm->players)) * j;
		tmp->pc = i;
		k = 0;
		tmp->start = i;
		while (k < tmp->size)
		{
			vm->memory[i] = tmp->data[k];
			i++;
			k++;
		}
		j++;
		tmp = tmp->next;
	}
}
