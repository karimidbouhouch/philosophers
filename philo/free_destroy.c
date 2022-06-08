/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 02:04:43 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/08 15:13:01 by kid-bouh         ###   ########.fr       */
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
		i++;
	}
	pthread_mutex_destroy(&all->lock->output);
	free(all->lock->forks);
	free(all->lock);
	free(all->philo);
}
