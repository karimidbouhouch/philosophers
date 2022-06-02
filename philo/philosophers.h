/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:08:33 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/02 22:55:27 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct mutex
{
	pthread_mutex_t *forks;
}	t_mutex;

typedef struct philo
{
	int id_philo;
	pthread_mutex_t right_fork;
	pthread_mutex_t left_fork;
}	t_philo;

typedef struct data
{
	int	nb_of_philo;
	int time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_meals;
	t_mutex *mutex;
	t_philo philo;
}	t_data;

int	ft_atoi(const char *str);

#endif