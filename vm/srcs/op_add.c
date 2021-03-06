/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 18:12:20 by yabdulha          #+#    #+#             */
/*   Updated: 2018/08/22 12:54:37 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Take three registries, add up the first two and store the result in third.
*/

void		op_add(t_vm *vm, t_champ *champ)
{
	t_params	*p;

	if (!(resolve_params(champ, champ->params, 1 + 2)))
	{
		champ->carry = 0;
		return ;
	}
	p = champ->params;
	put_reg(vm, champ, p->p3, p->p1 + p->p2);
	if (p->p1 + p->p2 == 0)
		champ->carry = 1;
	else
		champ->carry = 0;
}
