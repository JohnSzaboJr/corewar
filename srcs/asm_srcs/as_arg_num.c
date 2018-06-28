/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_arg_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/25 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"

int as_arg_num(int argc)
{
    if (argc != 2)
    {
        ft_printf("%s\n", "usage: ./asm [champion filename]");
        return (0);
    }
    return (1);
}