/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:07:01 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/01 22:38:55 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
	t_data data;

	if(ac < 5 || ac > 6)
	{
		printf("Error\n");
		return (1);
	}
	data.nb_of_philo = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data.nb_of_meals = ft_atoi(av[5]);

	printf("number_of_philosophers : %d\ntime_to_die : %d\ntime_to_eat:%d\ntime_to_sleep : %d\n \
	number_of_times_each_philosopher_must_eat : %d\n",data.nb_of_philo,data.time_to_die,data.time_to_eat,
	data.time_to_sleep,data.nb_of_meals);

	return (0);
}