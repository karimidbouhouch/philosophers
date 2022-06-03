/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:07:01 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/04 00:53:11 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex(t_all_data *all)
{
	int	i;

	i = 0;
	while (i < all->data->nb_of_philo)
		pthread_mutex_destroy(&all->mutex->forks[i++]);
	pthread_mutex_destroy(&all->mutex->output);
}

long	get_time()
{
	struct timeval	time;
	long			res;

	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

void	output(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->mutex->output);
	if (philo->data->flag == 1)
		return ;
	else if (philo->data->flag == 0)
	{
		printf("%ld\tThe philo %d %s\n", get_time() - philo->start_time, philo->id_philo, str);
		pthread_mutex_unlock(&philo->mutex->output);
	}
}

void	is_sleep(long wait_time)
{
	long	starting_time;
	long	time_passed;

	starting_time = get_time();
	time_passed = get_time() + wait_time;
	while (time_passed > starting_time)
	{
		usleep(100);
		starting_time = get_time();
	}
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	output(philo, "has taken the right fork");
	pthread_mutex_lock(&philo->left_fork);
	output(philo, "has taken the left fork");
	output(philo, "is eating");
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*data;

	data = (t_philo *)philo;
	data->last_meal = get_time();
	pthread_detach(data->thread);
	while (1)
	{
		if (data->eat_count != 0)
		{
			eating(data);
			data->last_meal = get_time();
			data->eat_count--;
			is_sleep(data->data->time_to_eat);
			pthread_mutex_unlock(&data->left_fork);
			pthread_mutex_unlock(&data->right_fork);
			output(data, "is sleeping");
			is_sleep(data->data->time_to_sleep);
			output(data, "is thinking");
		}
		else
			break ;
	}
	return (NULL);
}

int	make_thread(t_all_data *data, int flag, int i)
{
	if (data->philo[i].id_philo % 2 == flag)
	{
		data->philo[i].start_time = data->data->time;
		data->philo[i].mutex = malloc(sizeof(t_mutex));
		if (!data->philo[i].mutex)
		{
			destroy_mutex(data);
			free(data->mutex);
			free(data->mutex->forks);
			return (printf("Memory is not allocated"));
		}
		if (pthread_create(&data->philo[i].thread, NULL,
				&routine, &data->philo[i]) != 0)
		{
			destroy_mutex(data);
			free(data->mutex);
			free(data->mutex->forks);
			return (printf("Thread can't be created"));
		}
	}
	usleep(30);
	return (0);
}

int	thread(t_all_data *info)
{
	int	i;

	i = -1;
	info->data->time = get_time();
	while (++i < info->data->nb_of_philo)
		make_thread(info, 0, i);
	i = -1;
	usleep(50);
	while (++i < info->data->nb_of_philo)
		make_thread(info, 1, i);
	// if (pthread_create(&info->death, NULL, &check_death, info) != 0)
	// 	return (put_err("Thread can't be created", false));
	// if (pthread_join(info->death, NULL) != 0)
	// 	return (put_err("Threaf can't be joined", 0));
	// free_and_destroy(info);
	return (0);
}

int init_philo(t_all_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->data->nb_of_philo);
	if(!data->philo)
		return (1);
	while (i < data->data->nb_of_philo)
	{
		data->philo[i].id_philo = i + 1;
		data->philo[i].eat_count = data->data->nb_of_meals;
		data->philo[i].right_fork = data->mutex->forks[i];
		if ((i + 1) == data->data->nb_of_philo)
			data->philo[i].left_fork = data->mutex->forks[0];
		else
			data->philo[i].left_fork = data->mutex->forks[i + 1];
		i++;
	}
	return (0);
}

int init_mutex(t_all_data *data)
{
	int	i;

	i = 0;
	data->mutex = malloc(sizeof(t_mutex));
	if(!data->mutex)
		return (1);
	data->mutex->forks = malloc(sizeof(pthread_mutex_t) * data->data->nb_of_philo);
	if(!data->mutex->forks)
		return (1);
	while (i < data->data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->mutex->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_all_data infos;
	t_data data;

	infos.data = &data;
	if(ac < 5 || ac > 6)
	{
		printf("Error\n");
		return (1);
	}
	infos.data->nb_of_philo = ft_atoi(av[1]);
	infos.data->time_to_die = ft_atoi(av[2]);
	infos.data->time_to_eat = ft_atoi(av[3]);
	infos.data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		infos.data->nb_of_meals = ft_atoi(av[5]);
	init_mutex(&infos);
	init_philo(&infos);
	thread(&infos);

	// while(1)
	// {
	// 	printf("%ld\n",get_time());
	// 	sleep(1);
	// }

	return (0);
}