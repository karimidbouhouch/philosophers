/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:07:01 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/09 17:55:19 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_loop(t_all *all)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (i < all->data->nb_of_philo)
	{
		waitpid(-1, &status, 0);
		if (status == 0)
		{
			j = 0;
			while (j < all->data->nb_of_philo)
			{
				kill(all->philo->pid[j], SIGTERM);
				j++;
			}
		}
		i++;
	}
}

void	*check_death(void *philos)
{
	t_philo		*phil;
	int			meals_count;
	long		hunger_time;

	phil = (t_philo *)philos;
	while (1)
	{
		meals_count = 0;
		hunger_time = current_time() - phil->last_meal;
		if (phil->args->time_to_die < hunger_time)
		{
			sem_wait(phil->sems->output);
			printf("%ld\tThe philo %d is dead\n", current_time() - phil->args->start_time, phil->philo_id);
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
		printf("%ld\tThe philo %d %s\n", current_time() - philo->args->start_time, philo->philo_id, str);
	sem_post(philo->sems->output);
}

void	start_act(t_philo *phil)
{
	pthread_t	dead_flag;

	phil->args->start_time = current_time();
	phil->last_meal = current_time();
	pthread_create(&dead_flag, NULL, check_death, (void *)phil);
	pthread_detach(dead_flag);
	while (1)
	{
		if (phil->eat_count != 0)
		{
			sem_wait(phil->sems->forks);
			output(phil, "has taken the forks");
			output(phil, "is eating");
			phil->last_meal = current_time();
			ft_sleep(phil->args->time_to_eat);
			sem_post(phil->sems->forks);
			phil->eat_count--;
			output(phil, "is sleeping");
			ft_sleep(phil->args->time_to_sleep);
			output(phil, "is thinking");
		}
		else
			exit (0);
	}
}

int	init_process(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data->nb_of_philo)
	{
		all->philo->pid[i] = fork();
		if (all->philo->pid[i] == 0)
		{
			all->philo->philo_id = i + 1;
			start_act(all->philo);
		}
		else if (all->philo->pid[i] == -1)
			return (1);
		i++;
	}
	// wait_loop(all);
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
	if (init_sems(&info))
		return (0);
	if (init_philo(&info))
		return (0);
	if (init_process(&info))
		return (0);
	return (0);
}
