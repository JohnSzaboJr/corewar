/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse_errors_labels.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/19 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

int  as_params_parse_init(int *i, char *line, int *params_size)
{
    int j;

    *i = 0;
    as_k(1);
    *params_size = (as_get_pos(0, 0) != 0 && as_get_pos(0, 0) != 8 &&
    as_get_pos(0, 0) != 11) ? (0) : (1);
    *i = as_skip_label(line, i) + 1;
    as_skip_space(line, i);
    j = as_get_op_pos(line, *i);
    as_get_pos(op_tab[j].opcode, 1);
    as_skip_command(line, i);
    j = *i;
    as_skip_space(line, i);
    if (!line[*i])
        return (0);
    return (*i > j + 1) ? (2) : (1);
}

int as_bw_params_el(int *i, char *line, t_list_error **error)
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
    return (1);
}

static int as_check_dir_chars(char *line, int i, int j, t_list_error **error)
{
    char    c;
    int     k;

    k = i;
    while (line[i] != DIRECT_CHAR && !ft_isspace(line[i]))
        i--;
    if (k != i && line[i] != DIRECT_CHAR)
    {
        if (!as_add_error(error, ERROR20, line, k))
            return (0);
        return (-1);
    }
    i = k;
    c = line[i];
    line[i] = '\0';
    if (ft_hasnondigits(line + j + 1))
    {
        line[i] = c;
        if (!as_add_error(error, ERROR11, line, j + 1))
            return (0);
        return (-1);
    }
    line[i] = c;
    return (1);
}

int as_check_dir_length(char *line, int i, int j, t_list_error **error)
{
    char c;

    c = line[i];
    line[i] = '\0';
    if (ft_atoll(line + j + 1) > 2147483647 ||
    ft_atoll(line + j + 1) < -2147483648 ||
    ft_strlen(line + j + 1) > 11)
    {
        line[i] = c;
        if (!as_add_error(error, ERROR26, line, j + 2))
            return (0);
        return (-1);
    }
    // itt is ellenorizni h valojaban 2 vagy 4???
    line[i] = c;
    return (1);
}

int as_check_dir(char *line, int *i, int j, t_list_error **error)
{
    int ret;

    ret = 0;
    as_skip_rev_space(line, i);
    if (!(ret = as_check_dir_chars(line, *i, j, error)))
        return (0);
    if (ret != -1 && !(ret = as_check_dir_length(line, *i, j, error)))
        return (0);
    return (ret == -1) ? (-1) : (1);
}

static int as_check_ind_chars(char *line, int i, int j, t_list_error **error)
{
    char    c;

    c = line[i];
    line[i] = '\0';
    if (ft_hasnondigits(line + j))
    {
        line[i] = c;
        if (!as_add_error(error, ERROR11, line, j + 1))
            return (0);
        return (-1);
    }
    line[i] = c;
    return (1);
}

int as_check_ind_length(char *line, int i, int j, t_list_error **error)
{
    char    c;
    int     warning;

    warning = 0;
    c = line[i];
    line[i] = '\0';
    if (ft_atoll(line + j) > 32767 ||
    ft_atoll(line + j) < -32768 ||
    ft_strlen(line + j) > 6)
    {
        line[i] = c;
        if (!as_add_error(error, ERROR27, line, j + 1))
            return (0);
        return (-1);
    }
    if (ft_atoi(line + j) > IDX_MOD)
        warning = 1;
    line[i] = c;
    if (warning && !as_add_warning(error, WARNING12, line, j + 1))
        return (0);
    return (1);
}

int as_check_ind(char *line, int *i, int j, t_list_error **error)
{
    int ret;

    ret = 0;
    as_skip_rev_space(line, i);
    if (!(ret = as_check_ind_chars(line, *i, j, error)))
        return (0);
    if (ret != -1 && !(ret = as_check_ind_length(line, *i, j, error)))
        return (0);
    return (ret == -1) ? (-1) : (1);
}

int as_type_e(int co, int k, int a)
{
    const int   tab[12] =
    {T_REG, T_REG + T_DIR, T_REG + T_IND, T_REG + T_DIR + T_IND,
    T_DIR, T_REG + T_DIR, T_IND + T_DIR, T_REG + T_DIR + T_IND,
    T_IND, T_REG + T_IND, T_DIR + T_IND, T_REG + T_DIR + T_IND};

    if (k <= op_tab[co].param_count &&
    op_tab[co].param_type[k - 1] != tab[a] &&
    op_tab[co].param_type[k - 1] != tab[a + 1] &&
    op_tab[co].param_type[k - 1] != tab[a + 2] &&
    op_tab[co].param_type[k - 1] != tab[a + 3])
        return (-1);
    return (1);
}
