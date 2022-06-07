/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kid-bouh <kid-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:08:33 by kid-bouh          #+#    #+#             */
/*   Updated: 2022/06/07 02:35:58 by kid-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct mutex
{
	pthread_mutex_t	output;
	pthread_mutex_t	*forks;
}					t_mutex;

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
	int				philo_id;
	int				eat_count;
	long			last_meal;
	t_data			*args;
	t_mutex			*mutex;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_philo;

typedef struct all
{
	t_mutex		*lock;
	t_philo		*philo;
	t_data		*data;
}				t_all;

int		ft_atoi(const char *str);
int		init_philo(t_all *info);
int		init_mutex(t_all *info);
void	destroy_mutex(t_all *all);
void	free_and_destroy(t_all *all);
int		init_mutex(t_all *info);
int		init_philo(t_all *info);
void	output(t_philo *philo, char *str);
void	*routine(void *philo);
void	routine_2(t_philo *data);
int		make_thread(t_all *info, int j, int i);
int		if_dead(t_philo *philo);
int		ft_threads(t_all *info);
int		check_death(t_all *info);
long	current_time(void);
void	ft_sleep(long time);

#endif