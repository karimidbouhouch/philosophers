/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 02:25:28 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/10 22:57:28 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *v)
{
	int			meals_count;
	long		time;
	t_philo		*phil;

	phil = (t_philo *)v;
	while (1)
	{
		meals_count = 0;
		time = current_time() - phil->last_meal;
		if (time > phil->args->time_to_die)
		{
			sem_wait(phil->sems->output);
			printf("%ld\tThe philo %d is dead\n", current_time()
				- phil->args->start_time, phil->philo_id);
			exit (0);
		}
		meals_count += phil->eat_count;
		if (meals_count == 0)
		{
			sem_wait(phil->sems->output);
			exit (0);
		}
	}
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

void	output(t_philo *philo, char *str)
{
	sem_wait(philo->sems->output);
	if (philo->args->dead == 0)
		printf("%ld\tThe philo %d %s\n", current_time()
			- philo->args->start_time, philo->philo_id, str);
	sem_post(philo->sems->output);
}

void	routine(t_philo *philo)
{
	pthread_t	thread;

	philo->args->start_time = current_time();
	philo->last_meal = current_time();
	pthread_create(&thread, NULL, check_death, (void *)philo);
	pthread_detach(thread);
	while (1)
	{
		if (philo->eat_count != 0)
		{
			sem_wait(philo->sems->forks);
			output(philo, "has taken the forks");
			output(philo, "is eating");
			philo->last_meal = current_time();
			ft_sleep(philo->args->time_to_eat);
			sem_post(philo->sems->forks);
			philo->eat_count--;
			output(philo, "is sleeping");
			ft_sleep(philo->args->time_to_sleep);
			output(philo, "is thinking");
		}
		else
			return ;
	}
}
