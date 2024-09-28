/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:40:59 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/09/28 18:49:35 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf/ft_printf.h"

/*static void	print_values(int amount_of_bits, int signal_nbr)
{
	ft_printf("Bits read: %d\n", amount_of_bits);
	if (signal_nbr == SIGUSR1)
		ft_printf("Received SIGUSR1\n");
	else if (signal_nbr == SIGUSR2)
		ft_printf("Received SIGUSR2\n");
}*/

void	set_signal_handlers(int signal_nbr)
{
	static int				bits;
	static unsigned char	current_char;

	current_char <<= 1;
	if (signal_nbr == SIGUSR1)
		current_char |= 1;
	bits++;
	if (bits == 8)
	{
		ft_printf("%c", current_char);
		bits = 0;
		current_char = 0;
	}
//	print_values(bits, signal_nbr);
}

int	main(void)
{
	ft_printf("Server's pid: %d\n", getpid());
	signal(SIGUSR1, set_signal_handlers);
	signal(SIGUSR2, set_signal_handlers);
	while (1)
		pause();
	return (0);
}
