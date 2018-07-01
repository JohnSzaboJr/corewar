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

typedef struct				s_list_byte
{
	unsigned char					byte;
	struct s_list_byte		*next;
}							t_list_byte;

typedef struct				s_list_label
{
	char					*name;
	int						pos;
	struct s_list_label		*next;
}							t_list_label;

typedef struct	s_op
{
	char		*opname;
	int			param_count;
	int			param_type[3];
	int			opcode;
	int			cycles;
	char		*description;
	int			acb;
	int			half_size;
}				t_op;

extern t_op		op_tab[17];

int							as_arg_num(int argc);
int							as_open(char *filename, int *fd);
int							as_parse(int fd);
int							as_parse_name(char *line, int *section, t_list_byte **code);
int							as_parse_comment(char *line, int *section, t_list_byte **code);
int							as_store_magic(t_list_byte **code);
int							as_free(t_list_byte **list);
int							as_error(t_list_byte **code, int error_code);
void						as_print_list(t_list_byte *list, t_list_label *label);
int							as_reverse_list(t_list_byte **list);
int							as_parse_name_check(int *i, char *line, t_list_byte **code, int *length);
int							as_save_name(int *i, char *line, t_list_byte **code, t_list_byte **new);
int							as_parse_comment_check(int *i, char *line, t_list_byte **code, int *length);
int							as_save_comment(int *i, char *line, t_list_byte **code, t_list_byte **new);
int							as_parse_commands(char *line, int *section, t_list_byte **code, t_list_label **label);
int							as_code_size(t_list_byte *code);

#endif