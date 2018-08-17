/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 20:31:55 by yabdulha          #+#    #+#             */
/*   Updated: 2018/08/12 20:44:10 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_byte	*create_byte(t_vm *vm)
{
	t_byte	*new;

	if (!(new = (t_byte*)malloc(sizeof(t_byte))))
		error_exit(vm, "Malloc fail in read_bytes");
	return (new);
}

void	read_bytes(t_vm *vm, t_champ *champ, char *buff, int len)
{
	t_byte	*new;
	t_byte	*tmp;

	tmp = champ->bytes;
	while (tmp && tmp->next)
		tmp = tmp->next;
	while (len--)
	{
		new = create_byte(vm);
		new->byte = *buff;
		if (tmp)
			tmp->next = new;
		else
			champ->bytes = new;
		tmp = new;
		buff++;
	}
}

static int	determine_no(t_vm *vm, int no)
{
	int		i;
	t_champ	*tmp;

	i = 1;
	tmp = vm->champs;
	while (tmp)
	{
		if (tmp->number == i || tmp->number == -i ||
		tmp->number == -no)
		{
			tmp = vm->champs;
			i++;
			if (i > MAX_PLAYERS)
				i = 1;
		}
		tmp = tmp->next;
	}
	if (no != 0)
	{
		tmp = vm->champs;
		while (tmp)
		{
			if (tmp->number == -no)
				tmp->number = i;
			tmp = tmp->next;
		}
	}
	return (no == 0) ? (i) : (no);
}

int		reader(t_vm *vm, int no, char *path)
{
	int		fd;
	int		total_read;
	int		read_num;
	char	buffer[READ_BUFF_SIZE];
	t_champ	*champ;

	no = determine_no(vm, no);
	if ((fd = open(path, O_RDONLY)) < 0)
		error_exit(vm, "Can't open file");
	total_read = 0;
	champ = create_champ(vm);
	champ->filename = path;
	champ->number = no;
	champ->reg[0] = no;
	while ((read_num = read(fd, buffer, READ_BUFF_SIZE)) > 0)
	{
		if (total_read > CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH)
			error_exit(vm, "File too large");
		total_read += read_num;
		read_bytes(vm, champ, buffer, read_num);
		ft_bzero(buffer, READ_BUFF_SIZE);
	}
	if (total_read < 4)
		error_exit(vm, "File too small");
	add_champ(vm, champ);
	vm->players += 1;
	parse_bytes(vm, champ);
	return (0);
}