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
        ft_printf(WHITE " (as_save_name)\n" RESET);
    if (error_code == 1)
        ft_printf("%s\n", "");
    if (error_code == 2)
        ft_printf("%s\n", "ERROR: malloc error in as_parse_comment");
    if (error_code == 3)
        ft_printf("%s\n", "ERROR: comment incorrectly specified in source");
    if (error_code == 4)
        ft_printf("%s\n", "");
    if (error_code == 5)
        ft_printf("%s\n", "");
    if (error_code == 6)
        ft_printf("%s\n", "ERROR: comment is too long");
    if (error_code == 7)
        ft_printf("%s\n", "ERROR: malloc error in as_save_comment");
    if (error_code == 8)
        ft_printf("%s\n", "ERROR: malloc error in as_parse_commands");
    return (0);
// put these in a header?
}
