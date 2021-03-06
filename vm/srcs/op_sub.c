/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 15:41:43 by yabdulha          #+#    #+#             */
/*   Updated: 2018/08/22 16:51:24 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	Take three registries, substracts the second from the first parameter
**	and store the result in the third one, which is a register.
*/

void		op_sub(t_vm *vm, t_champ *champ)
{
	t_params	*p;

	if (resolve_params(champ, champ->params, 3) == 0)
		return ;
	p = champ->params;
	put_reg(vm, champ, p->p3, p->p1 - p->p2);
	if (p->p1 - p->p2 == 0)
		champ->carry = 1;
	else
		champ->carry = 0;
}
