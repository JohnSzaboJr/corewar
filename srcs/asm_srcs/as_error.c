/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/28 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

int as_error(t_list_num **code, int error_code)
{
    as_free(code);
    if (error_code == 0)
        ft_printf("%s\n", "ERROR: malloc error in as_parse_name");
    if (error_code == 1)
        ft_printf("%s\n", "ERROR: name incorrectly specified in source");
    if (error_code == 2)
        ft_printf("%s\n", "ERROR: malloc error in as_parse_comment");
    if (error_code == 3)
        ft_printf("%s\n", "ERROR: comment incorrectly specified in source");
    return (0);
}
