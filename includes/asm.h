/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 15:20:40 by jszabo            #+#    #+#             */
/*   Updated: 2018/03/26 15:01:07 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

typedef struct				s_list_num
{
	int						num;
	struct s_list_num		*next;
}							t_list_num;

int							as_arg_num(int argc);
int							as_open(char *filename, int *fd);
int							as_parse(int fd);
int							as_parse_name(char *line, int *section, t_list_num **code);
int							as_store_magic(t_list_num **code);
int							as_free(t_list_num **list);

#endif