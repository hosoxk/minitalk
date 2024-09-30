/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:40:59 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/09/30 17:20:15 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf/ft_printf.h"

void	handler(int signal_nbr)
{
	static int	bits;
	static int	i;

	if (signal_nbr == SIGUSR1)
		i |= (0x01 << bits);
	bits++;
	if (bits == 8)
	{
		ft_printf("%c", i);
		bits = 0;
		i = 0;
	}
}

int	main(void)
{
	ft_printf("Server's pid: %d\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		;
}
