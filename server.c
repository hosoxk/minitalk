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

typedef struct s_data
{
	int	bits;
	char	character;
	int	client_pid;
}	t_data;

t_data	g_data;
/*static void	print_values(int amount_of_bits, int signal_nbr)
{
	ft_printf("Bits read: %d\n", amount_of_bits);
	if (signal_nbr == SIGUSR1)
		ft_printf("Received SIGUSR1\n");
	else if (signal_nbr == SIGUSR2)
		ft_printf("Received SIGUSR2\n");
}*/

void	set_data(void)
{
	g_data.bits = 0;
	g_data.character = 0;
	g_data.client_pid = 0;
}

void	handler(int signal_nbr, siginfo_t *info, void *ucontext)
{
	(void)ucontext;

	if (g_data.client_pid != info->si_pid)
	{
		set_data();
		g_data.client_pid = info->si_pid;
	}
	g_data.character <<= 1;
	if (signal_nbr == SIGUSR2)
		g_data.character |= 1;
	g_data.bits++;
	if (g_data.bits == 8)
	{
		ft_printf("%c", g_data.character);
		set_data();
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server's pid: %d\n", getpid());
	set_data();

	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
