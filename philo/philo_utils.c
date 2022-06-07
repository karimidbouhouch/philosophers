/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:11:04 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/07 02:19:48 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	current_time(void)
{
	struct timeval	time;
	long			tmp;

	gettimeofday(&time, NULL);
	tmp = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (tmp);
}

void	ft_sleep(long time)
{
	long	start_time;
	long	time_passed;

	start_time = current_time();
	time_passed = current_time() + time;
	while (time_passed > start_time)
	{
		usleep(100);
		start_time = current_time();
	}
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	n;

	sign = 1;
	i = 0;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	return (n * sign);
}
