/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybazylbe <ybazylbe@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:31:57 by ybazylbe          #+#    #+#             */
/*   Updated: 2024/04/08 14:32:38 by ybazylbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_sendmsg(int pid, int c)
{
	int	bit;

	bit = 7;
	while (bit != -1)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(400);
		bit--;
	}
	return (0);
}

void	ft_client_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		write(1, "Received a signal\n", 19);
	}
}

int	main(int argc, char *argv[])
{
	int				pid;
	unsigned char	*str;

	if (argc == 3)
	{
		signal(SIGUSR1, ft_client_handler);
		pid = ft_atoi(argv[1]);
		str = (unsigned char *)argv[2];
		while (*str)
		{
			ft_sendmsg(pid,*str++);
		}
	}
	else
	{
		write(1, "invalid args", 13);
	}
	return (0);
}
