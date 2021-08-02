/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 04:10:36 by jagarcia          #+#    #+#             */
/*   Updated: 2021/02/01 02:59:26 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void	packer(t_woody data)
{
	Elf64_Shdr	texthdr;

	texthdr = search_section(".text", data.data, data.sheader, data.header);
	//encrypt(data.data + texthdr.sh_offset, texthdr.sh_size);
	data.new_entry = prepare_elf(data, &data.text_idx, &data.key);
	save_pack(data);
}
