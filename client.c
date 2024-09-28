/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:30:55 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/09/27 13:34:44 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//for usleep
#include <unistd.h>
//for kill
#include <signal.h>
#include "./ft_printf/ft_printf.h"
#include "./libft/libft.h"

int	g_wait = 0;

void	receive_signals(int index)
{
	if (index == SIGUSR1)
		g_wait++;
	if (g_wait == 8)
		g_wait = 0;
}

void	send_signal(int pid, unsigned char character)
{
	int				i;
	unsigned char	temp_char;

	i = 8;
	temp_char = character;
	while (i > 0)
	{
		if (g_wait != i)
			pause();
		temp_char = character >> (i - 1);
		if (temp_char % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
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
	}
	pid = ft_atoi(argv[1]);
	msg = argv[2];
	i = 0;
	while (msg[i] != '\0')
	{
		send_signal(pid, msg[i]);
		i++;
	}
	return (0);
}
