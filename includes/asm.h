/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:20:40 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/18 15:01:07 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

typedef struct				s_list_byte
{
	unsigned char			byte;
	int						type;
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

typedef struct	s_flags
{
	int			w;
	int			W;
	int			p;
}				t_flags;

extern t_op		op_tab[17];

// Functions to store information (filename)

int							as_get_params(char *line, t_list_label **label, t_list_byte **code);
int							as_get_command(char *line, int i, t_list_byte **code);
int							as_store_zero(int i, int section, t_list_byte **code);
int							as_store_non_zero(int length, char *line, int *i, t_list_byte **code);
int							as_store(int fd, t_list_label **label, char *filename, t_flags *flags);

// Functions to free memory allocation

int							as_free(t_list_byte **list);
int							as_free_error(t_list_error **list);
int							as_free_lab_fla(t_list_label **list, t_flags *flags);
int							as_free_line(char *line);

// Functions to print error/warning messages on stderr

void						as_errnbr(int n);
int							as_print_error(t_list_error **error, t_list_label **label, t_flags *flags);
int							as_war1(char *message, int line_nr, char *line, int column_nr);
int							as_err1(char *message, int line_nr, char *line, int column_nr);
int							as_err2(char *message, char *filename);
int							as_err3(char *message);
int							as_malloc_error1(t_list_error **error, int a);
int							as_malloc_error2(t_list_byte **code, int a);
void						as_write_err_line(char *line, int column_nr);
void						as_write_err_sign(char *line, int column_nr);
int							as_write_err(char *message, int line_nr, int column_nr, int e);
int							as_note_cmd(int line_nr, char *line, int column_nr);
int							as_note_reg(int line_nr, int column_nr);
int							as_note_type(int line_nr, int column_nr, char *message);
int							as_note_label(int line_nr, int column_nr, char *message);
void						as_label_error(char *message, int lnr, char *line, int cnr);

// Functions to store errors before printing them

int							as_add_error(t_list_error **error, char *message, char *line, int column_nr);
int							as_add_warning(t_list_error **error, char *message, char *line, int column_nr);
int							as_add_warning2(t_list_error **error, char *message, char *line, int cnr);
int							as_add_note_type(t_list_error **error, char *message, char *line, int column_nr);
int							as_add_label_error(t_list_error **error, char *line, int column_nr, int j);
int							as_add_error_noline(t_list_error **error, char *message);
int							as_add_note_cmd(t_list_error **error, char *message, char *line, int cnr);
int							as_add_note_reg(t_list_error **error, char *message, char *line, int cnr);
char						*as_get_err_par(int co, int k);
char						*as_param_error(int a, int b, t_list_error **error);
void						as_del_label_errors(t_list_error **error, char *line, int i);
char						*as_label_sug(char *str, t_list_label *label);
int							as_add_note(t_list_error **error, char *message, int cnr);

// Functions to initialize function variables

int							as_parse_init(char **l, t_list_error **e, int *bc);
void						as_store_init(char **l, t_list_byte **c, t_list_byte **s, int *sec);
void						as_store_name_comment_init(char *line, int *i, int section, int *length);
int							as_gparams_init(int *i, t_list_byte **code, char *line, t_list_byte **encoding);
int							as_pparams_init(int *i, char *line, int *params_size);

// Functions to keep track of values for errors

int							as_line_nr(int a);
int							as_i(int value, int a);
int							as_j(int a, int i);
int							as_k(int a);
int							as_get_pos(unsigned char byte, int a);
int							as_empty_line(int a);
int							as_endcomment(char *line, int a);

// Functions to store direct parameters

int							as_sd(char *line, t_list_byte **code);
int							as_dlabel(char *line, t_list_label **label, int byte_pos, t_list_byte **code);
int							as_dir(char *line);

// Functions to store indirect parameters

int							as_si(char *line, t_list_byte **code);
int							as_ilabel(char *line, t_list_label **label, int byte_pos, t_list_byte **code);
int							as_ind(char *line);

// Functions to store other parameter data

int							as_cmp_label(t_list_label *label, char *line, int k);
int							as_enc(t_list_byte **encoding, int start);
int							as_slabel(char *line, int *i, t_list_error **error, t_list_label **label);

// Functions to check for errors

int							as_ec(char **line, t_list_error **error, int bc, int i);
int							as_lc(char *line, char *filename);
int							as_empty_line_check(t_list_error **error, int a, char *line);
int							as_unexp_check(t_list_error **error, char *line);
int							as_check_enough_params(t_list_error **error, char *line, int i);
int							as_check_valid_params(t_list_error **error, char *line);
int							as_name_check(int *i, char *line, t_list_error **error, int *bc);
int							as_comment_check(int *i, char *line, t_list_error **error, int *bc);
int							as_check_spaces_line(char *line, t_list_error **error);
int							as_check_max_length(char *line, t_list_error **error);
int							as_type_e(int co, int k, int a);

// Functions to check errors in parameters

int							as_i_e(char *line, int *i, t_list_error **error, int *params_size);
int							as_d_e(char *line, int *i, t_list_error **error, int *params_size);
int							as_r_e(char *line, int *i, t_list_error **error, int *params_size);

// Functions to parse file

int							as_pp_loop(char *l, t_list_label **lab, t_list_error **err, int *ps);
int         				as_p_ops(char *l, t_list_error **err, t_list_label **label, int *bc);
int							as_pname(char *line, int *section, t_list_error **error, int *byte_count);
int							as_pcomment(char *line, int *section, t_list_error **error, int *byte_count);
int							as_parse_loop(char *line, t_list_error **error, t_list_label **label, int *bc);

// General utility functions

int							as_code_size(t_list_byte *code);
int							as_reverse_error(t_list_error **list);
int							as_reverse_list(t_list_byte **list);
int							as_label_list_size(t_list_label *label);
int							as_get_op_pos(char *line, int i);
void						as_write_bytes(t_list_byte **code, int info, int n);
int							as_add_bytes(t_list_byte **code, int n, int type);
int							as_add_byte(t_list_byte **code, unsigned char byte, int type);
int							as_cmd_comp(char *cmd, char *str);
int							as_add_label(t_list_label **label, char *line, int i, int pos);

// Functions to skip certain areas in string

int							as_skip_space(char *line, int *i);
int							as_skip_label(char *line, int *i);
int							as_skip_command(char *line, int *i);
int							as_skip_name(char *line, int *i, int *j);
int							as_skip_rev_space(char *line, int *i);
int							as_skip_to_params(char *line, int *i);
int							as_skip_to_sep(char *line, int *i);
int							as_skip_to_next_param(char *line, t_list_error **error, int *i);

// Output functions

int							as_write_file(t_list_byte **code, char *filename);
int							as_print_list(t_list_byte *list);

//

int	as_skip_label2(char *line, int *i);

#endif