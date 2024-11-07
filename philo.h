/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:47:20 by caqueiro           #+#    #+#             */
/*   Updated: 2024/11/07 12:16:15 by caqueiro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_arguments
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_philo_eat;
	int				error;
}					t_arguments;

t_arguments			parser(int argc, char **argv);
void				print_args(t_arguments args);

int					sleep_in_ms(int ms);
long long			ms_time(struct timeval *start);

typedef struct s_table
{
	pthread_mutex_t	*forks;
	int				*forks_status;
	pthread_mutex_t	forks_status_mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_mutex;
	int				dead_flag;
	t_arguments		args;
	struct timeval	tv_start;
}					t_table;

int					init_table(t_table *table, t_arguments args);

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	struct s_table	*table;
	pthread_mutex_t	meal_mutex;
}					t_philosopher;

int					init_philosophers(t_philosopher *philosophers,
						t_table *table);
void				destroy_table(t_table *table);
void				*philosopher_routine(void *arg);
void				smart_sleep(long long interval, struct timeval *start,
						t_philosopher *philo);
int					has_death(t_table *table, t_philosopher *philo);

int					monitor(t_table *table, t_philosopher *philos);

#endif
