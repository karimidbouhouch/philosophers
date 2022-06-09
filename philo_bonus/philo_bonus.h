/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:08:33 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/09 17:12:59 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/stat.h>
#include <signal.h>

typedef struct sema
{
	sem_t	*output;
	sem_t	*forks;
}			t_sema;

typedef struct data
{
	long	start_time;
	int		dead;
	int		nb_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_of_meals;
}			t_data;

typedef struct philo
{
	int		philo_id;
	int		eat_count;
	long	last_meal;
	t_data	*args;
	t_sema	*sems;
	pid_t	*pid;
}			t_philo;

typedef struct all
{
	t_sema	*lock;
	t_philo	*philo;
	t_data	*data;
}			t_all;

int		ft_atoi(const char *str);
void	destroy_mutex(t_all *all);
void	free_and_destroy(t_all *all);
int		init_philo(t_all *info);
void	output(t_philo *philo, char *str);
void	start_act(t_philo *phil);
void	*check_death(void *philos);
long	current_time(void);
void	ft_sleep(long time);
int		ft_parse(char **av);
int		ft_isdigit(int c);
void	wait_loop(t_all *all);
int		init_process(t_all *all);
int		init_sems(t_all *info);



#endif