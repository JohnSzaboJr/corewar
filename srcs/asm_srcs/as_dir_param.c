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

//  int as_check_dir(char *line, int *i, int j, int line_nr)
// {
//     as_skip_rev_space(line, i);
//     if (!as_check_r_chars(line, *i, j, line_nr) || 
//     !as_check_r_length(line, *i, j, line_nr) ||
//     !as_check_r_zero(line, *i, j, line_nr))
//         return (0);
//     return (1);
// }

//  int  as_check_errors_dir(int line_nr, char *line, int *i, t_list_byte **code)
// {
//     int j;

//     j = as_j(0, 0);
//     if (!line[j + 1] || ft_isspace(line[j + 1]) || line[j + 1] == SEPARATOR_CHAR)
//         as_err1(ERROR12, line_nr, line, j + 2);
//     else if (line[j + 1])
//     {
//         if (!as_check_dir(line, i, j, line_nr))
//             return (0);
//         else if (!as_check_r_params(as_get_pos((*code)->byte, 0), as_k(0)))
//         {
//             as_err1(ERROR15, line_nr, line, j + 1);
//             as_err_note3(line_nr, j + 1, as_get_pos((*code)->byte, 0), as_k(0));
//             return (0);
//         }
//     }
//     return (1);
// }

static int  as_tmp_label(int get, int a)
{
    static int  pos = 0;

    if (a == 1)
        pos = get;
    return (pos);
}


int as_s_label(t_list_byte **code, t_list_byte **encoding, char *line)
{
    int k;
    int i;
    int pos;

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
    i = (!ft_strncmp(line + 1, "sti", 3)) ? (2) : (4);
    while (i)
    {
        if (!as_add_byte(code, 0))
            return (0);
        i--;
    }
    // itt kell hozzaadni, ha van valodi eredmeny.
    if (as_tmp_label(0, 0))
        ft_printf("pos to save here: %d\n", as_tmp_label(0, 0));

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


    // ha LABEL_CHAR a kovetkezo:
    // while LABEL_CHARS i++
    // ha 0 LABEL_CHARS, es utana (skip space), vege vagy SEPARATOR_CHAR:
    // missing label ERROR
    // ha 0 LABEL_CHARS, es utana (skip space) mas karakterek
    // invalid label ERROR
    // a LABEL_CHARS utan '\0' charactert rakni
    // megnezni a line vegso reszet
    // 3 opcio: 
    // 1: ez egy letezo label, pozitiv value-val

    // ekkor a recordingolni a relativ helyet, es az encodingot is
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

int as_dir(char *line)
{
    if (line[as_j(0, 0)] == DIRECT_CHAR)
        return (1);
    return (0);
}