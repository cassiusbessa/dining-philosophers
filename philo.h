/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassius <cassius@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:47:20 by cassius           #+#    #+#             */
/*   Updated: 2024/11/02 00:59:44 by cassius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# define SECONDS_IN_MINUTE 60;
# define SECONDS_IN_HOUR 3600;
# define SECONDS_IN_DAY 86400;
# define DAYS_IN_YEAR 365;

typedef struct s_arguments {
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	int	error;
} t_arguments;

t_arguments	parser(int argc, char **argv);
void	print_args(t_arguments args);

int	sleep_in_ms(int ms);
int	time_stamp_in_ms(struct timeval *start);
void	print_current_time(struct timeval *tv_start);

#endif
