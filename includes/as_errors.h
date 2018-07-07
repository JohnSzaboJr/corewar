/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   as_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jszabo <jszabo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 15:20:40 by jszabo            #+#    #+#             */
/*   Updated: 2018/03/26 15:01:07 by jszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AS_ERRORS_H
# define AS_ERRORS_H

#define MAX_LINE_LENGTH 50
#define MAX_ERROR_SIZE 40
#define LABEL_SIZE 20
#define ERROR0      " malloc failure"
#define ERROR1      " name specifier string incorrect\n"
#define ERROR2      " missing quotation mark before name\n"
#define ERROR3      " missing name\n"
#define ERROR4      " missing quotation mark after name\n"
#define ERROR5      " missing quotation mark before comment\n"
#define ERROR6      " missing quotation mark after comment\n"
#define ERROR7      " comment specifier string incorrect\n"
#define ERROR8      " unknown operation\n"
#define ERROR9      " missing parameters\n"
#define ERROR10      " label too long\n"
#define ERROR11      " invalid parameter\n"
#define ERROR12      " register number missing from parameter\n"
#define ERROR13      " register number is too long\n"
#define ERROR14      " register number is zero\n"
#define ERROR15      " incompatible parameter\n"
#define ERROR16      " too many parameters for this type of operation\n"
#define ERROR17      " line exceeds maximum length\n"
#define ERROR18      " too few parameters for this type of operation, "
#define ERROR19      " line exceeds maximum length\n"
#define ERROR20      " invalid characters at the end of parameter\n"
#define ERROR21      " direct reference missing from parameter\n"
#define ERROR22      " missing label\n"
#define ERROR23      " invalid label\n"
#define WARNING1    " no space after name specifier\n"
#define WARNING2    " invalid character(s) after name\n"
#define WARNING3    " name too long\n"
#define WARNING4    " no space after comment specifier\n"
#define WARNING5    " missing comment\n"
#define WARNING6    " invalid character(s) after comment\n"
#define WARNING7    " comment too long\n"
#define WARNING8    " space before argument separator\n"
#define WARNING9    " unnecessary space before parameter\n"
#define WARNING10    " space at the end of the line\n"

#endif