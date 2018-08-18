/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 16:20:18 by yabdulha          #+#    #+#             */
/*   Updated: 2018/08/16 14:39:32 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "flag_handler.h"

int		main(int ac, char **av)
{
	// visualizer offset
	// dump vs visualizer
	// meg meg kell irni az actual valtozasokat amit a flagek letrehoznak...
	// norm and build in latest build
	// add to matrix
	t_vm	*vm;
	int		i;

	vm = create_vm(ac, av);
	fl_get(ac, av, vm);
	load_processes(vm);
	printf(CLEAR);
	i = 2800;
	while (vm->cycles++ < 6000)
	{
		run_champs(vm);
		fl_write_matrix(vm);
	 	// if (i < vm->cycles && (vm->cycles % 1) == 0)
		// 	dump_handler(vm);
	}
	return (0);
}
