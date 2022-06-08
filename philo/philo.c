/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:07:01 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/08 15:11:36 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	make_thread(t_all *info, int j, int i)
{
	if (info->philo[i].philo_id % 2 == j)
	{
		if (pthread_create(&info->philo[i].thread, NULL,
				&routine, &info->philo[i]) != 0)
		{
			destroy_mutex(info);
			free(info->lock);
			free(info->lock->forks);
			return (1);
		}
	}
	usleep(30);
	return (0);
}

int	if_dead(t_philo *philo)
{
	long	time;

	time = current_time() - philo->last_meal;
	if (time > philo->args->time_to_die)
	{
		pthread_mutex_lock(&philo->mutex->output);
		printf("%ld\tThe philo %d is dead\n",
			current_time() - philo->args->start_time, philo->philo_id);
		philo->args->dead = 1;
		return (1);
	}
	return (0);
}

int	check_death(t_all *info)
{
	int	i;
	int	count_meals;

	while (1)
	{
		i = 0;
		count_meals = 0;
		while (i < info->data->nb_of_philo)
		{
			if (if_dead(&info->philo[i]))
				return (1);
			count_meals += info->philo[i].eat_count;
			i++;
		}
		if (count_meals == 0)
		{
			pthread_mutex_lock(&info->lock->output);
			return (1);
		}
	}
	return (0);
}

int	ft_threads(t_all *info)
{
	int	i;

	i = -1;
	info->data->start_time = current_time();
	while (++i < info->data->nb_of_philo)
		make_thread(info, 0, i);
	i = -1;
	while (++i < info->data->nb_of_philo)
		make_thread(info, 1, i);
	if (check_death(info))
		return (0);
	return (0);
}

int	main(int ac, char **av)
{
	t_all	info;
	t_data	data;

	info.data = &data;
	if (ac < 5 || ac > 6)
		return (1);
	if (ft_parse(av))
		return (0);
	info.data->nb_of_philo = ft_atoi(av[1]);
	info.data->time_to_die = ft_atoi(av[2]);
	info.data->time_to_eat = ft_atoi(av[3]);
	info.data->time_to_sleep = ft_atoi(av[4]);
	info.data->nb_of_meals = -1;
	info.data->dead = 0;
	if (av[5] != NULL)
		info.data->nb_of_meals = ft_atoi(av[5]);
	if (init_mutex(&info))
		return (0);
	if (init_philo(&info))
		return (0);
	if (ft_threads(&info))
		return (0);
	free_and_destroy(&info);
	return (0);
}
