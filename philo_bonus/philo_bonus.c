/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:07:01 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/10 22:51:09 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_loop(t_all *all)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	waitpid(-1, &status, 0);
	while (i < all->data->nb_of_philo)
	{
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

int	init_process(t_all *all)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (i < all->data->nb_of_philo)
	{
		all->philo->pid[i] = fork();
		if (all->philo->pid[i] == 0)
		{
			all->philo->philo_id = i + 1;
			routine(all->philo);
		}
		else if (all->philo->pid[i] == -1)
			return (1);
		i++;
	}
	wait_loop(all);
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
	free_all(&info);
	return (0);
}
