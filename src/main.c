/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:20:21 by jagarcia          #+#    #+#             */
/*   Updated: 2021/01/26 06:43:07 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static t_woody	prepare_data(char *filename)
{
	t_woody data;
	int		fd;

	if ((fd = open(filename, O_RDWR)) < 0)
		woody_error(OPEN_ERROR);
	syscall(SYS_fstat, fd, &data.dstat);
	if (!(data.data = mmap(NULL, data.dstat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)))
		woody_error(MMAP_ERROR);
	if (close(fd) < 0)
		woody_error(CLOSE_ERROR);
	if ((fd = open("./covid", O_RDWR)) < 0)
		woody_error(OPEN_ERROR);
	syscall(SYS_fstat, fd, &data.astat);
	if (!(data.asm_data = mmap(NULL, data.astat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)))
		woody_error(MMAP_ERROR);
	if (close(fd) < 0)
		woody_error(CLOSE_ERROR);
	return (data);
}

int main(int argn, char **argv)
{
	int		file;
	t_woody	data;
	
	if (!(file = set_flags(argv, argn)))
		return (0);
	data = prepare_data(argv[file]);
	data.header = *(Elf64_Ehdr *)(data.data);
	data.sheader = (Elf64_Shdr *)(data.data + data.header.e_shoff);
	data.pheader = (Elf64_Phdr *)(data.data + data.header.e_phoff);
	packer(data);	
	if ((munmap(data.data, data.dstat.st_size) < 0))
		woody_error(MUNMAP_ERROR);
	if ((munmap(data.asm_data, data.astat.st_size) < 0))
		woody_error(MUNMAP_ERROR);
}
