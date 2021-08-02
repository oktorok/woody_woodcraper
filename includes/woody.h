/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:03:30 by jagarcia          #+#    #+#             */
/*   Updated: 2021/02/01 20:48:05 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
#define WOODY_H

#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include "libft.h"

#define OPEN_ERROR "Error opening file"
#define MMAP_ERROR "Error mmapping memory"
#define MUNMAP_ERROR "Error munmapping memory"
#define WRITE_ERROR "Error writing file"
#define CLOSE_ERROR "Error closing file"
#define ASMFILE_ERROR "Error finding correct spot on asm"

#define ENTRY_DESP 0xa0
#define TEXT_DESP 0xa4
#define MAGIC_KEY	0x406b6540
#define MAGIC_ENTRY	0x40656e40
#define MAGIC_TEXT 	0x40746540
#define MAGIC_SIZE	0x40736940

typedef struct	s_woody
{
	void		*data;
	void		*asm_data;
	struct stat	dstat;
	struct stat astat;
	Elf64_Ehdr	header;
	int			text_idx;
	size_t		new_entry;
	int			key;
	Elf64_Shdr	*sheader;
	Elf64_Phdr	*pheader;
}				t_woody;

char		check_flag(int to_check);
int			set_flags(char **argv, int argn);
int			main(int argc, char **argv);
void		woody_error(char *err);
void		*get_data(int fd, size_t offset, size_t len);
Elf64_Shdr	search_section(char *sect_name, void *data, Elf64_Shdr *sections, Elf64_Ehdr header);
void		packer(t_woody data);
void		save_pack(t_woody data);
void		encrypt(void *data, size_t size);
size_t		prepare_elf(t_woody data, int *text_idx, int *key);

#endif
