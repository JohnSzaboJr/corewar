/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/25 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include <fcntl.h>

int as_open(char *filename, int *fd)
{
    if (0 > ((*fd) = open(filename, O_RDONLY)))
    {
        ft_printf("%s\n", "ERROR: invalid filepath");
        return (0);
    }
    return (1);
}
