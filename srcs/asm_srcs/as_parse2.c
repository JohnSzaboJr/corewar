/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/20 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

static int  as_lab_e(int j, char *line, t_list_error **err, t_list_label **lab)
{
    int     k;
    char    c;

    k = j;
    as_skip_space(line, &j);
    if (j > k && line[j] && line[j] != SEPARATOR_CHAR)
        return (as_add_error(err, ERROR23, line, k + 1));
    k = j;
    as_skip_label(line, &j);
    if (!(j - k))
    {
        as_skip_space(line, &j);
        if (!line[j] || line[j] == SEPARATOR_CHAR)
            return (as_add_error(err, ERROR22, line, j));
    }
    c = line[j];
    line[j] = '\0';
    if (!as_cmp_label(*lab, line, k))
    {
        line[j] = c;
        return (as_add_label_error(err, line, k, j));
    }
    line[j] = c;
    return (1);
}

static int  as_dlab_e(char *line, t_list_label **label, t_list_error **error)
{
    int     j;

    j = as_j(0, 0);
    if (line[j + 1] == LABEL_CHAR)
    {
        if ((-1 == as_type_e(as_get_pos(0, 0), as_k(0), 4)) &&
        !as_add_error(error, ERROR15, line, j + 1))
            return (0);
        return (as_lab_e(j + 2, line, error, label));
    }
    return (-1);
}

int         as_pp_loop(char *l, t_list_label **lab, t_list_error **err, int *ps)
{
    int ret;
    int i;

    ret = 0;
    i = as_i(0, 0);
    if (!as_bw_params_el(&i, l, err) || ((l[as_j(0, 0)] == 'r') &&
    !as_r_e(l, &i, err, ps)) || (as_dir(l) && !(ret = as_dlab_e(l, lab, err))))
        return (0);
    if (as_dir(l) && ret != -1)
        *ps = *ps + 2;
    else if (as_dir(l) && ret == -1 && !as_d_e(l, &i, err, ps))
        return (0);
    if (as_ind(l) == 2 && (((-1 == as_type_e(as_get_pos(0, 0), as_k(0), 4)) &&
    !as_add_error(err, ERROR15, l, as_j(0, 0) + 1)) ||
    !as_lab_e(as_j(0, 0) + 1, l, err, lab)))
        return (0);
    if (as_ind(l) == 2)
        *ps = *ps + 2;
    if ((as_ind(l) == 1 && !as_i_e(l, &i, err, ps)) ||
    (!as_check_valid_params(err, l) || !as_skip_to_next_param(l, err, &i)))
        return (0);
    as_i(i, 1);
    return (1);
}
