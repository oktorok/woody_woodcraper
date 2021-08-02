/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagarcia <jagarcia@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:41:49 by jagarcia          #+#    #+#             */
/*   Updated: 2021/01/23 23:59:39 by jagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static int	print_help_func(void)
{
	ft_putstr("command: woody [OPTION] [FILE]\n\n");
	ft_putstr("OPTIONS:\n \
\t-h: help\n");
	return (0);
}

int			set_flags(char **argv, int argn)
{
	int	flags;
	int	ns;
	int	i;

	flags = 0;
	if (argn < 2)
		return (print_help_func());
	i = 1;
	while (i < argn && argv[i][0] == '-')
	{
		ns = 0;
		while (argv[i][ns] == '-')
			ns++;
		if (argv[i][ns] == 'h')
			return (print_help_func());
		flags |= (1 << (argv[i++][ns] - 'a'));
	}
	if (i == argn)
		return (print_help_func());
	check_flag(flags);
	return (i);
}

char		check_flag(int to_check)
{
	static int flags = -1;

	if (flags < 0)
	{
		flags = to_check;
		return (0);
	}
	if (flags & (1 << (to_check - 'a')))
		return (1);
	return (0);
}
