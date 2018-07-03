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
#include "as_errors.h"
#include "colors.h"
#include <fcntl.h>

int as_error(t_list_byte **code, int error_code)
{
    as_free(code);
    ft_printf(BOLDYELLOW "\nsystem error:" RESET);
	ft_printf(BOLDWHITE ERROR0 RESET);
    if (error_code == 0)
        ft_printf(WHITE " (as_parse_name)\n" RESET);
    if (error_code == 1)
        ft_printf(WHITE " (as_parse_comment)\n" RESET);
    if (error_code == 2)
        ft_printf(WHITE " (as_parse_commands)\n" RESET);
    if (error_code == 3)
        ft_printf(WHITE " (as_get_command)\n" RESET);
    return (0);
}
