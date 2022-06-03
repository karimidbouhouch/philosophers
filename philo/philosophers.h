/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:08:33 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/04 00:32:59 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct mutex
{
	pthread_mutex_t *forks;
	pthread_mutex_t output;
}	t_mutex;

typedef struct data
{
	long time;
	int	flag;
	int	nb_of_philo;
	int time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_meals;
}	t_data;

typedef struct philo
{
	int		id_philo;
	int		eat_count;
	long	last_meal;
	long	start_time;
	pthread_t thread;
	pthread_mutex_t right_fork;
	pthread_mutex_t left_fork;
	t_mutex *mutex;
	t_data *data;
}	t_philo;

typedef struct all_data
{
	t_philo *philo;
	t_data *data;
	t_mutex *mutex;
}	t_all_data;



int	ft_atoi(const char *str);

#endif