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
	unsigned char			byte;
	struct s_list_byte		*next;
}							t_list_byte;

typedef struct				s_list_label
{
	char					*name;
	int						pos;
	struct s_list_label		*next;
}							t_list_label;

typedef struct				s_list_error
{
	int						type;
	char					*line;
	char					*message;
	int						line_nr;
	int						column_nr;
	struct s_list_error		*next;
}							t_list_error;

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

// Functions to store information (filename)

int							as_store_magic(t_list_byte **code);
int							as_store_name_comment(char *line, int *section, t_list_byte **code, t_list_byte **size);
int							as_store_commands(char *line, t_list_byte **code, t_list_label **label);
int							as_store_size(t_list_byte **size, t_list_byte *code);

// Functions to free data

int							as_free(t_list_byte **list);
int							as_free_error(t_list_error **list);
int							as_free_label(t_list_label **list);
int							as_free_line(char *line);

// Functions to print error/warning messages on stderr

int							as_war1(char *message, int line_nr, char *line, int column_nr);
int							as_err1(char *message, int line_nr, char *line, int column_nr);
int							as_err2(char *message, char *filename);
int							as_err3(char *message);

// Functions to initialize functions

int							as_parse_init(char **l, t_list_error **e, int *sec, int *bc);
void						as_store_init(char **l, t_list_byte **c, t_list_byte **s, int *sec);

//

int							as_err_note(int line_nr, char *line, int column_nr);
int							as_err_note2(int line_nr, int column_nr);
int							as_err_note3(int line_nr, int column_nr, int co, int k);
void						as_write_err(char *message, int line_nr, int column_nr, int e);
void						as_write_err_line(char *line, int column_nr);
void						as_write_err_sign(char *line, int column_nr);
int							as_add_error(t_list_error **error, char *message, char *line, int column_nr);
int							as_add_warning(t_list_error **error, char *message, char *line, int column_nr);
int							as_add_note(t_list_error **error, char *message, char *line, int column_nr);
int							as_add_label_error(t_list_error **error, char *message, char *line, int column_nr);
int							as_add_error_noline(t_list_error **error, char *message);
int							as_add_error_note1(t_list_error **error, char *message, char *line, int column_nr);
int							as_print_error(t_list_error *error);

void						as_print_list(t_list_byte *list, t_list_label *label);
int							as_reverse_list(t_list_byte **list);
int							as_parse_name_check(int *i, char *line, t_list_error **error);
int							as_parse_comment_check(int *i, char *line, t_list_error **error);
int							as_code_size(t_list_byte *code);

int							as_skip_space(char *line, int *i);
int							as_skip_label(char *line, int *i);
int							as_skip_command(char *line, int *i);
int							as_skip_name(char *line, int *i, int *j);
int							as_skip_rev_space(char *line, int *i);
int							as_skip_to_params(char *line, int *i);
int							as_skip_to_sep(char *line, int *i);
int							as_skip_to_next_param(char *line, t_list_error **error, int *i);

int							as_cmd_comp(char *cmd, char *str);
int							as_add_byte(t_list_byte **code, unsigned char byte);
int							as_add_label(t_list_label **label, char *line, int i, int pos);

int							as_check_r_chars(char *line, int i, int j, t_list_error **error);
int							as_check_r_length(char *line, int i, int j, t_list_error **error);
int							as_check_r_zero(char *line, int i, int j, t_list_error **error);
int							as_check_r_params(int co, int k);
int							as_add_r_encoding(int co, int k, t_list_byte **encoding);
int							as_s_reg(t_list_byte **code, t_list_byte **encoding, char *line);

int							as_dir(char *line);
int							as_dir_label(char *line);
int							as_dir_label2(char *line, t_list_label **label, int byte_pos, t_list_byte **code);

int							as_k(int a);
int							as_j(int a, int i);
int							as_get_pos(unsigned char byte, int a);
int							as_check_enough_params(t_list_error **error, char *line, int i);
int							as_check_valid_params(t_list_error **error, char *line);

int							as_line_nr(int a);

int							as_parse_name(char *line, int *section, t_list_error **error, int *byte_count);
int							as_parse_comment(char *line, int *section, t_list_error **error, int *byte_count);
int							as_parse_commands(char *line, t_list_error **error, t_list_label **label, int *byte_count);

int							as_init_i_k_pos_params(int *i, t_list_byte **code, char *line, t_list_byte **encoding);
int							as_check_r(char *line, int *i, int j, t_list_error **error);
int							as_cmp_label(t_list_label *label, char *line, int k);

int							as_reverse_error(t_list_error **list);

int							as_store_dir(char *line, t_list_byte **code);

int							as_store_ind(char *line, t_list_byte **code);
int							as_ind_encoding(t_list_byte **encoding);
int							as_dir_encoding(t_list_byte **encoding);

#endif