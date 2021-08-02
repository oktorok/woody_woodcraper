/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_section.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 00:42:00 by jagarcia          #+#    #+#             */
/*   Updated: 2021/01/24 05:03:45 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

Elf64_Shdr	search_section(char *sect_name, void *data, Elf64_Shdr *sections, Elf64_Ehdr header)
{
	char		*strtable;
	int			i;

	strtable = (char *)(data + sections[header.e_shstrndx].sh_offset);
	i = 0;
	while (i < header.e_shnum)
	{
		if (!ft_strcmp(strtable + sections[i].sh_name, sect_name))
			break;
		i++;
	}
	return (sections[i]);
}
