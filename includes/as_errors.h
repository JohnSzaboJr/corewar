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
#define USAGE      "./asm [filename.s]\n"
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
#define ERROR13      " register doesn't exist\n"
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
#define ERROR24      " duplicate label\n"
#define ERROR25      " direct reference missing from parameter\n"
#define ERROR26      " direct reference number is too long\n"
#define ERROR27      " direct reference number is too long\n"
#define ERROR28      " label reference not found\n"
#define ERROR29      " source file incomplete\n"
#define ERROR30      "no such file: "
#define ERROR31      "not a valid source file: "
#define ERROR32      " compiled size would exceed maximum length\n"
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
#define WARNING11    " unnecessary spaces between operation and parameter\n"
#define WARNING12    " indirect reference too far\n"
// reg_number note...
#define NOTE1       " choose a register number lower than REG_NUMBER to silence this warning\n"
#define NOTE2       " choose a number that fits in 4 bytes to silence this warning\n"
#define NOTE3       " choose a number that fits in 2 bytes to silence this warning\n"

#endif