/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabdulha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 16:20:18 by yabdulha          #+#    #+#             */
/*   Updated: 2018/08/16 14:39:32 by yabdulha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fl_write_opcode(int fd, t_vm *vm)
{
	char	*num;
	t_champ *tmp;

	tmp = vm->champs;
	write(fd, " [[", 3);
	while (tmp)
	{
		if (!(num = ft_itoa(tmp->opcode)))
			error_exit(vm, "malloc failure in fl_write_opcode");
		free(num);
		write(fd, num, ft_strlen(num));
		if (tmp->next)
			write(fd, ", ", 2);
		tmp = tmp->next;
	}
	write(fd, "], [", 4);
}

void	fl_write_memory(int fd, t_vm *vm)
{
	int		i;
	int		val;
	char	*num;
	t_champ *tmp;

	i = 0;
	fl_write_opcode(fd, vm);
	while (i < MEM_SIZE)
	{
		tmp = vm->champs;
		val = (unsigned char)(vm->memory)[i];
		while (tmp)
		{
			val = (tmp->pc == i) ? val + 1000 : val;
			tmp = tmp->next;
		}
		if (!(num = ft_itoa(val)))
			error_exit(vm, "malloc failure in fl_write_memory");
		write(fd, num, ft_strlen(num));
		free(num);
		if (i < MEM_SIZE - 1)
			write(fd, ", ", 2);
		i++;
	}
	write(fd, "]]", 2); 
}

void	fl_write_champ(int fd, t_vm *vm)
{
	char	*num;
	t_champ *tmp;

	tmp = vm->champs;
	write(fd, "var champs = [", 14);
	while (tmp)
	{
		write(fd, "[\"", 2);
		write(fd, tmp->name, ft_strlen(tmp->name));
		write(fd, "\", ", 3);
		if(!(num = ft_itoa(tmp->number)))
			error_exit(vm, "malloc failure in fl_write_champ");
		write(fd, num, ft_strlen(num));
		free(num);
		write(fd, "]", 1);
		if (tmp->next)
			write(fd, ", ", 1);
		tmp = tmp->next;
	}
	write(fd, "];\n", 3);
	write(fd, "var memory = [", 14); 
}

void	fl_write_matrix(t_vm *vm)
{
	static int	fd = 0;
	static int i = 0;

	if (!i)
	{
		fd = open("./matrix/memory.js", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR |
		S_IWUSR | S_IRGRP | S_IROTH);
		fl_write_champ(fd, vm);
	}
	fl_write_memory(fd, vm);
	if (i < 6000)
		write(fd, ",", 1);
	if (i == 6000 - 1)
	{
		write(fd, "];\n", 3);
		close(fd);
		system("open -a \"Google Chrome\" ./matrix/matrix.html");
	}
	i++;
}

int		champs_num(t_champ *champ)
{
	t_champ *tmp;
	int i;

	tmp = champ;
	i = 0;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (0);
}

int		fl_dump(char **av, t_vm *vm, int *i, int ac)
{
	static int	dump_ct = 0;

	if (dump_ct > 0)
		error_exit(vm, USE);
	if (!ft_strcmp(av[*i], "-dump"))
	{
		dump_ct++;
		vm->flags += 268435456;
		(*i)++;
		if (*i == ac || !ft_isnumber(av[*i]) || ft_isspace(av[*i][0]) ||
		av[*i][0] == "-" || av[*i][0] == "+")
			error_exit(vm, USE);
		if (ft_strlen(av[*i]) > 5)
			error_exit(vm, "cycle number has to be under 100000");
		vm->offset = ft_atoi(av[*i]);
		if (vm->offset < 1)
			error_exit(vm, USE);
		(*i)++;
	}
	if (*i == ac)
		return (0);
	return (1);
}

int		fl_n(char **av, t_vm *vm, int *i, int ac)
{
	int nr;
	t_champ *tmp;

	nr = 0;
	tmp = vm->champs;
	if (!ft_strcmp(av[*i], "-n"))
	{
		vm->flags += 262144;
		(*i)++;
		if (*i == ac || !ft_isnumber(av[*i]) || ft_isspace(av[*i][0]) ||
		av[*i][0] == "-" || av[*i][0] == "+")
			error_exit(vm, USE);
		if (ft_strlen(av[*i] > 10) || ft_atoi_l(av[*i]) > 2147483647)
		nr = ft_atoi(av[*i]);
		if (nr < 1)
			error_exit(vm, "player number too small");
		if (nr > MAX_PLAYERS)
			error_exit(vm, "player number too large");
		while (tmp)
		{
			if (tmp->number == -nr)
				error_exit(vm, "same player number can't be assigned twice");
			tmp = tmp->next;
		}
		(*i)++;
		if (*i == ac || ft_strcmp(av[*i] + ft_strlen(av[*i]) - 4, ".cor"))
			error_exit(vm, USE);
		if (vm->champs && champs_num(vm->champs) >= MAX_PLAYERS)
			error_exit(vm, "too many champions");
		reader(vm, -nr, av[*i]);
		(*i)++;
	}
	if (*i == ac)
		return (0);
	return (1);
}

int		fl_v(char **av, t_vm *vm, int *i, int ac)
{
	static int	v_ct = 0;

	if (v_ct > 0)
		error_exit(vm, USE);
	if (!ft_strcmp(av[*i], "-v"))
	{
		v_ct++;
		vm->flags += 1024;
		(*i)++;
	}
	if (*i == ac)
		return (0);
	return (1);
}

int		fl_m(char **av, t_vm *vm, int *i, int ac)
{
	static int	m_ct = 0;

	if (m_ct > 0)
		error_exit(vm, USE);
	if (!ft_strcmp(av[*i], "-m"))
	{
		m_ct++;
		vm->flags += 524288;
		(*i)++;
	}
	if (*i == ac)
		return (0);
	return (1);
}

int		fl_champ(char **av, t_vm *vm, int *i, int ac)
{
	if ((av[*i][0] == '-') || ft_strcmp(av[*i] + ft_strlen(av[*i]) - 4, ".cor"))
			error_exit(vm, USE);
	if (vm->champs && champs_num(vm->champs) >= MAX_PLAYERS)
		error_exit(vm, "too many champions");
	reader(vm, 0, av[*i]);
	return (1);
}

void	fl_normalize_champ_nr(t_champ *champs)
{
	t_champ *tmp;

	tmp = champs;
	while (tmp)
	{
		if (tmp->number < 0)
			tmp->number = -(tmp->number);
		tmp = tmp->next;
	}
}

void	fl_get(int ac, char **av, t_vm *vm)
{
	int	i;

	i = 1;

	while (i < ac)
	{
		if (!fl_dump(av, vm, &i, ac) || 
			!fl_n(av, vm, &i, ac) ||
			!fl_v(av, vm, &i, ac) ||
			!fl_m(av, vm, &i, ac) ||
			!fl_champ(av, vm, &i, ac))
			break;
		i++;
	}
	fl_normalize_champ_nr(vm->champs);

	// give usage if it no flag
}

int		main(int ac, char **av)
{
	t_vm	*vm;
	int		i;

	vm = create_vm(ac, av);
	fl_get(ac, av, vm);
	load_processes(vm);
	printf(CLEAR);
	i = 2800;
	while (vm->cycles++ < 6000)
	{
		run_champs(vm);
		fl_write_matrix(vm);
	 	// if (i < vm->cycles && (vm->cycles % 1) == 0)
		// 	dump_handler(vm);
	}
	return (0);
}
