/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:30:55 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/10/04 16:37:15 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//for usleep
#include <unistd.h>
//for kill
#include <signal.h>
#include "./ft_printf/ft_printf.h"

volatile int	g_ack_received = 0;

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	ack_handler(int signal_nbr)
{
	(void)signal_nbr;
	g_ack_received = 1;
}

void	send_signal(int pid, char character)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_ack_received = 0;
		if (character & (0x01 << i))
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_printf("Error sending SIGUSR1\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_printf("Error sending SIGUSR2\n");
		}
		usleep(100);
		while (!g_ack_received)
			;
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*msg;
	int		i;
	int		pid;

	if (argc != 3 || !argv[2])
	{
		ft_printf("Error:\nCorrect usage of <%s>:"
			" <server's pid> <message>\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	msg = argv[2];
	signal(SIGUSR1, ack_handler);
	i = 0;
	while (msg[i] != '\0')
	{
		send_signal(pid, msg[i]);
		i++;
	}
	send_signal(pid, '\0');
	return (0);
}
