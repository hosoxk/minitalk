/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:40:59 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/10/04 16:35:04 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf/ft_printf.h"

void	handler(int signal_nbr, siginfo_t *info, void *context)
{
	static int	bits = 0;
	static int	i = 0;

	(void)context;
	if (signal_nbr == SIGUSR1)
		i |= (0x01 << bits);
	bits++;
	if (bits == 8)
	{
		if (i == 0)
			ft_printf("\n");
		else
			ft_printf("%c", i);
		bits = 0;
		i = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server's pid: %d\n", getpid());
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
