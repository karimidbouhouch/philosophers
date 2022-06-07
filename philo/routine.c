/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 02:25:28 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/07 02:31:40 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	output(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->mutex->output);
	if (philo->args->dead == 1)
		return ;
	else if (philo->args->dead == 0)
	{
		printf("%ld\tThe philo %d %s\n",
			current_time() - philo->args->start_time, philo->philo_id, str);
		pthread_mutex_unlock(&philo->mutex->output);
	}
}

void	routine_2(t_philo *data)
{
	pthread_mutex_lock(data->right_fork);
	output(data, "has taken the right fork");
	pthread_mutex_lock(data->left_fork);
	output(data, "has taken the left fork");
	output(data, "is eating");
	data->last_meal = current_time();
	data->eat_count--;
	ft_sleep(data->args->time_to_eat);
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
	output(data, "is sleeping");
	ft_sleep(data->args->time_to_sleep);
	output(data, "is thinking");
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->last_meal = current_time();
	while (1)
	{
		if (philo->eat_count != 0)
		{
			routine_2(philo);
		}
		else
			break ;
	}
	return (NULL);
}
