/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex_philo_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 02:01:50 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/08 17:59:55 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sems(t_all *info)
{
	info->lock = malloc(sizeof(t_sema));
	if (!info->lock)
		return (1);
	sem_unlink("output");
	info->lock->output = sem_open("output", O_CREAT, 0644, 1);
	if (info->lock->output == SEM_FAILED)
		return (1);
	info->lock->forks = sem_open("forks", O_CREAT, 0644, info->data->nb_of_philo);
	if (info->lock->forks == SEM_FAILED)
		return (1);
	return (0);
}

int	init_philo(t_all *info)
{
	int	i;

	i = 0;
	info->philo = malloc(sizeof(t_philo) * info->data->nb_of_philo);
	if (!info->philo)
		return (1);
	info->philo->pid = malloc(sizeof(pid_t) * info->data->nb_of_philo);
	if (!info->philo->pid)
		return (1);
	info->data->dead = 0;
	info->philo->eat_count = info->data->nb_of_meals;
	info->philo->args = info->data;
	info->philo->sems = info->lock;
	return (0);
}
