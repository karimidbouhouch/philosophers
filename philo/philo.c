/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:07:01 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/03 18:40:58 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if(!data->philo)
		return (1);
	while (i < data->nb_of_philo)
	{
		data->philo[i].id_philo = i + 1;
		data->philo[i].eat_count = data->nb_of_meals;
		data->philo[i].right_fork = data->mutex->forks[i];
		if ((i + 1) == data->nb_of_philo)
			data->philo[i].left_fork = data->mutex->forks[0];
		else
			data->philo[i].left_fork = data->mutex->forks[i + 1];
		i++;
	}
	return (0);
}

int init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->mutex = malloc(sizeof(t_mutex));
	if(!data->mutex)
		return (1);
	data->mutex->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if(!data->mutex->forks)
		return (1);
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->mutex->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

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
	struct timeval time;

	while(1)
	{
		gettimeofday(&time, NULL);
		printf("%ld\n",time.tv_sec * 1000 + time.tv_usec / 1000);
		usleep(800);
	}
		

	return (0);
}