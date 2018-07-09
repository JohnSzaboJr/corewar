/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse_errors_labels.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/06 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

static int  as_params_parse_init(int *i, char *line, int *params_size, int *ret)
{
    int j;

    j = 15;
    *i = 0;
    as_k(1);
    *params_size = 0;
    *ret = 0;
    *i = as_skip_label(line, i) + 1;
    as_skip_space(line, i);
    while (j >= 0)
    {
        if (!ft_strncmp(op_tab[j].opname, line + i, ft_strlen(op_tab[j].opname)))
            break ;
        j--;
    }
    as_get_pos(op_tab[j].opcode, 1);
    as_skip_command(line, i);
    as_skip_space(line, i);
    if (!line[*i])
        return (0);
    return (1);
}

static void  as_bw_params_el(int *i, char *line, t_list_error **error)
{
    as_j(1, *i);
    as_skip_to_sep(line, i);
    as_k(2);
    if (as_k(0) > op_tab[as_get_pos(0, 0)].param_count &&
    !as_add_error(error, ERROR16, line, as_j(0, 0) + 1))
        return (0);
    if (line[*i] == SEPARATOR_CHAR && ft_isspace(line[*i - 1]) &&
    !as_add_warning(error, WARNING8, line, *i))
        return (0);
}

static int  as_check_errors_el_r(char *line, int *i, t_list_error **error, int *params_size)
{
    int j;
    int ret;

    ret = 0;
    j = as_j(0, 0);
    if (!line[j + 1] || ft_isspace(line[j + 1]) || line[j + 1] == SEPARATOR_CHAR)
    {
        ret = -1;
        if (!as_add_error(error, ERROR12, line, j + 2))
            return (0);
    }
    else if (line[j + 1])
    {
        if (!(ret = as_check_r(line, i, j, error)))
            return (0);
        if (ret != -1 && !as_check_r_params(as_get_pos(0, 0), as_k(0)))
        {
            ret = -1;
            if (!as_add_error(error, ERROR15, line, j + 1))
                return (0);
            //as_err_note3(line_nr, j + 1, as_get_pos(0, 0), as_k(0));
        }
    }
    if (ret != -1)
        (*params_size)++;
    return (1);
}

static int  as_cmp_label_el(t_list_label *label, char *line, int k)
{
    while (label)
    {
        if (!ft_strcmp(line + k, label->name))
            return (1);
        label = label->next;
    }
    return (0);
}

static int as_dir_el_label(char *line, t_list_label **label, t_list_error **error, int byte_count)
{
    int     j;
    int     k;
    char    c;

    j = as_j(0, 0);
    if (line[j + 1] == LABEL_CHAR)
    {
        j = j + 2;
        k = j;
        as_skip_space(line, &j);
        if (j > k && line[j] && line[j] != SEPARATOR_CHAR)
        {
            if (!as_add_error(error, ERROR23, line, k + 1))
                return (0);
            return (1);
        }
        k = j;
        as_skip_label(line, &j);
        if (!(j - k))
        {
            as_skip_space(line, &j);
            if (!line[j] || line[j] == SEPARATOR_CHAR)
            {
                if (!as_add_error(error, ERROR22, line, j))
                    return (0);
                return (1);
            }
        }
        c = line[j];
        line[j] = '\0';
        if (!as_cmp_label_el(*label, line, k))
        {
            if (!as_add_label_error(error, line + k, line, k))
                    return (0);
        }
        line[j] = c;
        return (1);
    }
    return (-1);
}

static int as_parse_el_params(char *line, t_list_label **label, t_list_error **error, int *byte_count)
{
    int             i;
    int             params;
    int             params_size;
    int             ret;

    params = as_params_parse_init(&i, line, &params_size, &ret);
    if (as_get_pos(0, 0) != 1 && as_get_pos(0, 0) != 9 &&
    as_get_pos(0, 0) != 12 && as_get_pos(0, 0) != 15 &&
    as_get_pos(0, 0) != 16)
        params_size++;
    while (line[i] && params)
    {   
        ret = 0;
        as_bw_params_el(&i, line, error);
        if ((line[as_j(0, 0)] == 'r') &&
        !as_check_errors_el_r(line, i, error, &params_size))
            return (0);
        if (as_dir(line) && !(ret = as_dir_el_label(line, label, error, byte_count)))
            return (0);
        if (as_dir(line) && ret != -1)
            params_size = params_size + 2;
        else if (as_dir(line) && ret == -1)
        {
            ft_printf("found direct\n");
        }
        if (ft_isdigit(line[as_j(0, 0)]) || line[as_j(0, 0)] == '-')
        {
            ft_printf("found indirect\n");
        }
        as_check_valid_params(line_nr, line);
        as_skip_to_next_param(line, line_nr, &i);
    }
    as_check_enough_params(code, line_nr, line, i);

    //
    if (!(*label))
        ft_printf("y\n");
    //
    *byte_count = *byte_count + params_size;
    return (1);
}

static int  as_parse_el_command(char *line, int i, t_list_error **error, int *byte_count)
{
    int         j;

    j = 15;
    while (j >= 0)
    {
        if (!ft_strncmp(op_tab[j].opname, line + i, ft_strlen(op_tab[j].opname)))
            break ;
        j--;
    }
    if (j == -1 || !ft_isspace(line[i + ft_strlen(op_tab[j].opname)]))
    {
        if (!as_add_error(error, ERROR8, line, i + 1))
            return (0);
        else
            return (-1);
    }
    (*byte_count)++;
    return (1);
}

int as_parse_el_name(char *line, int *section, t_list_error **error, int *byte_count)
{
	int			i;

	(*section)++;
	if (!(ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))) &&
		(ft_isspace(line[ft_strlen(NAME_CMD_STRING)]) ||
		line[ft_strlen(NAME_CMD_STRING)] == '"'))
	{
		if (!as_parse_name_check(&i, line, error))
			return (0);
        *byte_count = (*byte_count) + PROG_NAME_LENGTH + 4;
		return (1);
	}
    if (!as_add_error(error, ERROR1, line, 1))
        return (0);
	return (1);
}

int as_parse_el_comment(char *line, int *section, t_list_error **error, int *byte_count)
{
	int			i;

	(*section)++;
	if (!(ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING))) &&
		(ft_isspace(line[ft_strlen(COMMENT_CMD_STRING)]) ||
		line[ft_strlen(COMMENT_CMD_STRING)] == '"'))
	{
		if (!as_parse_comment_check(&i, line, error))
			return (0);
        *byte_count = (*byte_count) + COMMENT_LENGTH + 8;
		return (1);
	}
	if (!as_add_error(error, ERROR7, line, 1))
        return (0);
	return (1);
}

static void as_check_label_errors(t_list_error **error, char *line, int i)
{
    t_list_error    *node;
    t_list_error    *prev;

    node = *error;
    (*error) = (*error)->next;
    while (node->type == 4 && !ft_strncmp(node->message, line, i))
    {
        free(node->message);
        free(node->line);
        free(node);
        node = *error;
        *error = (*error)->next;
    }
    prev = node;
    while (*error)
    {
        if ((*error)->type == 4 && !ft_strncmp((*error)->message, line, i))
        {
            free((*error)->message);
            free((*error)->line);
            prev->next = (*error)->next;
            free(*error);
            *error = prev;
        }
        prev = *error;
        *error = (*error)->next;
    }
    *error = node;
}

int as_parse_el_commands(char *line, t_list_error **error, t_list_label **label, int *byte_count)
{
	int				i;
	int				ret;

	i = 0;
	ret = 0;
	if (ft_strlen(line) > MAX_LINE_LENGTH && !as_add_error(error, ERROR17, line, 1))
        return (0);
	if (as_skip_label(line, &i) && line[i] == LABEL_CHAR && i <= LABEL_SIZE)
	{
        as_check_label_errors(error, line, i);
        if (as_cmp_label_el(*label, line, 0))
        {
            if (!as_add_error(error, ERROR24, line, 1))
                return (0);
        }
		else if (!as_add_label(label, line, i, *byte_count))
		{
			as_free(error);
			return (0);
		}
		i++;
	}
	else if (i > LABEL_SIZE)
	{
        if (!as_add_error(error, ERROR10, line, i + 1))
            return (0);
		i++;
	}
	else
		i = 0;
	as_skip_space(line, &i);
	if (!line[i])
		return (1);
	if (!(ret = as_parse_el_command(line, i, error, byte_count)))
		return (0);	
	if (ret > -1 && !as_parse_el_params(line, label, error, byte_count))
		return (0);	

	

	// can label names be the same as known commands?	
	return (1);
}