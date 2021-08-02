/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_elf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:41:15 by jagarcia          #+#    #+#             */
/*   Updated: 2021/02/01 20:49:27 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static int		find_text(t_woody data, int *text_idx)
{
	char	*shstrtable;
	size_t	i;

	shstrtable = (char *)(data.data + data.sheader[data.header.e_shstrndx].sh_offset);
	i = 0;
	while (i < data.header.e_shnum)
	{
		if (!ft_strcmp(shstrtable + data.sheader[i].sh_name, ".text"))
		{
			*text_idx = i;
			break;
		}
		i++;
	}
	return (i);
}

static size_t	find_segment(t_woody data, int text_idx)
{
	size_t	new_entry;
	size_t	start;
	size_t	size;
	size_t	start_next;
	int		i;
	int		j;

	i = -1;
	new_entry = 0;
	while (++i < data.header.e_phnum - 1)
	{
		
		if (!(data.pheader[i].p_type & PT_LOAD))
			continue;
		start = data.pheader[i].p_vaddr;
		size = data.pheader[i].p_memsz;
		j = i - 1;
		start_next = data.pheader[i + 1].p_vaddr;
		if (start + size + data.astat.st_size < start_next)
		{
			new_entry = start + size;
			break;
		}
	}
	data.pheader[3].p_flags |= PF_W; //CAMBIAR
	data.pheader[i].p_flags |= PF_X;
	if (!new_entry)
		woody_error("No hay segmento");
	printf("segment =\t%d\nnew_entry =\t%#lx\n",i,new_entry);
	data.sheader[14].sh_size = 0x1000;
	return (new_entry);
}

size_t			prepare_elf(t_woody data, int *text_idx, int *key)
{
	char	*text_sect;
	size_t	new_entry;
	int		i;

	*text_idx = find_text(data, text_idx);
	text_sect = data.data + data.sheader[*text_idx].sh_addr;	
	i = 0;
	*key = 0x000042;
	while (i < data.sheader[*text_idx].sh_size)
		text_sect[i++] ^= *key;

	new_entry = find_segment(data, *text_idx);
}
