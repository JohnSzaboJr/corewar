/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 17:41:27 by jszabo            #+#    #+#             */
/*   Updated: 2018/08/18 17:41:28 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_HANDLER_H
# define FLAG_HANDLER_H
# include "vm.h"

void	fl_get(int ac, char **av, t_vm *vm);
int		fl_champ(char **av, t_vm *vm, int *i, int ac);
int		fl_n(char **av, t_vm *vm, int *i, int ac);
void	fl_normalize_champ_nr(t_vm *vm);
int		champs_num(t_champ *champ);
void	fl_write_matrix(t_vm *vm);
int		determine_no(t_vm *vm, int no);

#endif