/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:07:01 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/06 21:58:33 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data->nb_of_philo)
		pthread_mutex_destroy(&all->lock->forks[i++]);
	pthread_mutex_destroy(&all->lock->output);
}

void	free_and_destroy(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data->nb_of_philo)
	{
		pthread_mutex_destroy(all->philo[i].left_fork);
		pthread_mutex_destroy(all->philo[i].right_fork);
		// free(all->philo[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&all->lock->output);
	free(all->lock->forks);
	free(all->lock);
	free(all->philo);
}

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
		usleep(50);
		start_time = current_time();
	}
}

void	output(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->mutex->output);
	if (philo->args->dead == 1)
		return ;
	else if (philo->args->dead == 0)
	{
		printf("%ld\tThe philo %d %s\n", current_time() - philo->args->start_time, philo->philo_id, str);
		pthread_mutex_unlock(&philo->mutex->output);
	}
}

void	*routine(void *philo)
{
	t_philo	*data;

	data = (t_philo *)philo;
	data->last_meal = current_time();
	while (1)
	{
		if (data->eat_count != 0)
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
		else
			break ;
	}
	return (NULL);
}

int	make_thread(t_all *info, int j, int i)
{
	if (info->philo[i].philo_id % 2 == j)
	{
		if (pthread_create(&info->philo[i].thread, NULL, &routine, &info->philo[i]) != 0)
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
		printf("%ld\tThe philo %d is dead\n", current_time() - philo->args->start_time, philo->philo_id);
		philo->args->dead = 1;
		return (0);
	}
	return (1);
}

void	*check_death(void *info)
{
	t_all	*all;
	int		i;
	int		meals_count;

	all = (t_all *)info;
	while (1)
	{
		i = 0;
		meals_count = 0;
		while (i < all->data->nb_of_philo)
		{
			if (!if_dead(&all->philo[i]))
				return (NULL);
			meals_count += all->philo[i].eat_count;
			i++;
		}
		if (meals_count == 0)
		{
			pthread_mutex_lock(&all->lock->output);
			return (NULL);
		}
	}
}

int	init_mutex(t_all *info)
{
	int	j;

	j = 0;
	info->lock = malloc(sizeof(t_mutex));
	if (!info->lock)
		return (1);
	info->lock->forks = malloc(sizeof(pthread_mutex_t) * info->data->nb_of_philo);
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

int	main(int ac, char **av)
{
	t_all	info;
	t_data	data;
	int	i;

	info.data = &data;
	if (ac < 5 || ac > 6)
		return (1);
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
	i = -1;
	info.data->start_time = current_time();
	while (++i < info.data->nb_of_philo)
		make_thread(&info, 0, i);
	i = -1;
	while (++i < info.data->nb_of_philo)
		make_thread(&info, 1, i);
	
	int count_meals;
	while (1)
	{
		i = 0;
		count_meals = 0;
		while (i < info.data->nb_of_philo)
		{
			if (!if_dead(&info.philo[i]))
				return (1);
			count_meals +=  info.philo[i].eat_count;
			i++;
		}
		if (count_meals == 0)
		{
			pthread_mutex_lock(&info.lock->output);
			// return (1);
			while(1)
				pause();
		}
	}
	free_and_destroy(&info);
	destroy_mutex(&info);
	
	return (0);
}
