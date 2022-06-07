/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 02:01:50 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/07 02:31:07 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_all *info)
{
	int	j;

	j = 0;
	info->lock = malloc(sizeof(t_mutex));
	if (!info->lock)
		return (1);
	info->lock->forks = malloc(sizeof(pthread_mutex_t)
			* info->data->nb_of_philo);
	if (!info->lock->forks)
		return (1);
	if (pthread_mutex_init(&info->lock->output, NULL) != 0)
		return (1);
	while (j < info->data->nb_of_philo)
	{
		if (pthread_mutex_init(&info->lock->forks[j], NULL) != 0)
			return (1);
		j++;
	}
	return (0);
}

int	init_philo(t_all *info)
{
	int	i;

	i = 0;
	info->philo = malloc(sizeof(t_philo) * info->data->nb_of_philo);
	if (!info->philo)
		return (1);
	while (i < info->data->nb_of_philo)
	{
		info->philo[i].philo_id = i + 1;
		info->philo[i].last_meal = 0;
		info->philo[i].eat_count = info->data->nb_of_meals;
		info->philo[i].args = info->data;
		info->philo[i].mutex = info->lock;
		info->philo[i].right_fork = &info->lock->forks[i];
		if ((i + 1) == info->data->nb_of_philo)
			info->philo[i].left_fork = &info->lock->forks[0];
		else
			info->philo[i].left_fork = &info->lock->forks[i + 1];
		i++;
	}
	return (0);
}
