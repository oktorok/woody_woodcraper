/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_pack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 04:20:18 by jagarcia          #+#    #+#             */
/*   Updated: 2021/02/01 20:03:33 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static void	fill_covid(t_woody data, void *asm_data, size_t asize)
{
	void *match;

	if (!(match = ft_memchr(asm_data, MAGIC_ENTRY, asize)))
		woody_error(ASMFILE_ERROR);
	ft_bzero(match, sizeof(MAGIC_ENTRY));
	*((int *)match) = data.new_entry + ENTRY_DESP - data.header.e_entry;
	printf("NEW_ENTRY =\t%x\n", data.new_entry);
	printf("ENTRY =\t%#x\n", *((int *)match));
	if (!(match = ft_memchr(asm_data, MAGIC_KEY, asize)))
		woody_error(ASMFILE_ERROR);
	ft_bzero(match, sizeof(MAGIC_KEY));
	*((int *)match) = data.key;
	printf("KEY =\t%#x\n", *((int *)match));
	if (!(match = ft_memchr(asm_data, MAGIC_TEXT, asize)))
		woody_error(ASMFILE_ERROR);
	ft_bzero(match, sizeof(MAGIC_TEXT));
	*((int *)match) = data.new_entry + TEXT_DESP - data.sheader[data.text_idx].sh_addr;
	printf("TEXT =\t%#x\n", *((int *)match));
	if (!(match = ft_memchr(asm_data, MAGIC_SIZE, asize)))
		woody_error(ASMFILE_ERROR);
	ft_bzero(match, sizeof(MAGIC_SIZE));
	*((int *)match) = data.sheader[data.text_idx].sh_size;
	printf("SIZE =\t%#x\n", *((int *)match));
}
	
void	save_pack(t_woody data)
{
	int		fd;
	void *	match;
	size_t	data_match;
	
	if ((fd = open("./woody", O_WRONLY | O_CREAT | O_TRUNC, 0744)) < 0)
		woody_error(OPEN_ERROR);
	fill_covid(data, data.asm_data, data.astat.st_size);
	
	((Elf64_Ehdr *)data.data)[0].e_entry = data.new_entry; //AGREGAR UNA FUNCION QUE LOCALICE EL LUGAR
	ft_memcpy(data.data + data.new_entry, data.asm_data, data.astat.st_size);
	if (write(fd, data.data, data.dstat.st_size) < 0)
		woody_error(WRITE_ERROR);
	if (close(fd) < 0)
		woody_error(CLOSE_ERROR);
	return ;
}
