/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_dir_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 14:31:23 by jszabo            #+#    #+#             */
/*   Updated: 2018/07/06 14:35:38 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"
#include "asm.h"
#include "colors.h"
#include "as_errors.h"
#include <fcntl.h>

static int  as_tmp_label(int get, int a)
{
    static int  pos = 0;

    if (a == 1)
        pos = get;
    return (pos);
}

static void  as_convert_label(t_list_byte **code)
{
    int         label_bytes;
    t_list_byte *node;
    int         i;

    i = 0;
    node = *code;
    label_bytes = as_tmp_label(0, 0);
    if (label_bytes)
    {
        while (i < 2)
        {
            (*code)->byte = ((-label_bytes) >> (8 * i)) & 0xff;
            (*code) = (*code)->next;
            i++;
        }
        (*code) = node;
    }
}


int as_s_label(t_list_byte **code, t_list_byte **encoding, char *line)
{
    int         k;
    int         i;
    int         pos;

    i = 0;
    k = as_k(0);
    pos = as_get_pos((*code)->byte, 0);
    if (k <= op_tab[pos].param_count)
    {
        if (k == 1)
            (*encoding)->byte = (unsigned char)128;
        if (k == 2)
            (*encoding)->byte = (*encoding)->byte + (unsigned char)32;
        if (k == 3)
            (*encoding)->byte = (*encoding)->byte + (unsigned char)8;
    }
    as_skip_label(line, &i);
    if (line[i] == LABEL_CHAR)
        i++;
    as_skip_space(line, &i);
    i = 2;
    while (i)
    {
        if (!as_add_byte(code, 0))
            return (0);
        i--;
    }
    as_convert_label(code);
    return (1);
}

static int  as_cmp_label(t_list_label *label, char *line, int k, int pos)
{
    while (label)
    {
        if (!ft_strcmp(line + k, label->name) && label->pos > 0)
        {
            as_tmp_label(pos - (label->pos), 1);
            return (1);
        }
        label = label->next;
    }
    as_tmp_label(0, 1);
    // ha nem talal ilyet, akkor a helyi negativat rakja a tmp-be
    // amikor a labelt mentjuk az elejen, megnezzuk h van-e negativ
    // ha van, annak megfelelo helyre rakunk egyet
    // es a negativ szamot 0-ra valtoztatjuk
    // ha a vegen maradt negativ, akkor az annak megfelelo label
    // nem letezett!
    // hogyan rakunk standard errort? (line nr, column nr, line)
    // also: warning - unused label???
    return (0);
}

int as_dir_label(char *line, t_list_label **label, int byte_pos, t_list_byte **code)
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
            as_err1(ERROR23, as_line_nr(0), line, k + 1);
            return (0);
        }
        k = j;
        as_skip_label(line, &j);
        if (!(j - k))
        {
            as_skip_space(line, &j);
            if (!line[j] || line[j] == SEPARATOR_CHAR)
            {
                as_err1(ERROR22, as_line_nr(0), line, j);
                return (0);
            }
        }
        c = line[j];
        line[j] = '\0';
        if (as_cmp_label(*label, line, k, byte_pos))
            ft_printf("label match!\n");
        line[j] = c;
        return (1);
    }


    // mi van ha a label char utan space van?


 
    // 2: ez egy letezo label, negative value-val
    // ekkor csinalni egy uj labelt, az itt levo negative valueval
    // csinalni neki ures helyet
    // 3, ez nem egy letezo label
    // ekkor scinalni egy uj labelt az itt levo negative valueval
    // csinalni neki ures helyet


    // a label creation resz utan ellenorizni h van-e negativ
    // odamenni, es odairni a megfelelo value-t.
    // a file vegen ellenorizni h nem volt rendes label



    // visszaallitani a '\0' character helyett... (ha volt)
    // line_nr optimalizalni mindenutt!
    // live and zjmp don't have encoding byte!
    if (!(*code))
        ft_printf("y\n");
    return (0);
}

// int as_dir(char *line, int line_nr, int *i, t_list_byte **code)
// {
//     if ((line[as_j(0, 0)] == 'DIRECT_CHAR') &&
//     as_check_errors_dir(line_nr, line, i, code))
//         return (1);
//     return (0);
// }

// az elejen:
// ha DIRECT_CHAR &&
// ha nincs error azzal hogy: label_check
// errorokat a standard errorra???

int as_dir(char *line)
{
    if (line[as_j(0, 0)] == DIRECT_CHAR)
        return (1);
    return (0);
}