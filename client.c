/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:30:55 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/09/28 19:44:46 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//for usleep
#include <unistd.h>
//for kill
#include <signal.h>
#include "./ft_printf/ft_printf.h"

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

void	send_signal(int pid, char character)
{
	int		i;
	char	temp_char;

	i = 8;
	temp_char = character;
	while (i > 0)
	{
		temp_char = character >> (i - 1);
		if (temp_char % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(3000);
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
		return (1);
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
