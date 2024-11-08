/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:09:05 by caqueiro          #+#    #+#             */
/*   Updated: 2024/11/07 23:10:42 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	fork_lock(t_philosopher *philo);
static int	take_fork(t_philosopher *philo);

int	try_take_forks(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->table->args.number_of_philosophers;
	pthread_mutex_lock(&philo->table->forks_status_mutex);
	if (philo->table->forks_status[left_fork] == 0
		&& philo->table->forks_status[right_fork] == 0)
	{
		philo->table->forks_status[left_fork] = 1;
		philo->table->forks_status[right_fork] = 1;
		pthread_mutex_unlock(&philo->table->forks_status_mutex);
		if (take_fork(philo) == 2)
			return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->forks_status_mutex);
		return (0);
	}
	return (0);
}

static int	take_fork(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;
	int	tooken_forks;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->table->args.number_of_philosophers;
	tooken_forks = fork_lock(philo);
	if (!has_death(philo->table, philo) && tooken_forks == 2)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lld %d has taken a fork\n", ms_time(&philo->table->tv_start),
			philo->id);
		printf("%lld %d has taken a fork\n", ms_time(&philo->table->tv_start),
			philo->id);
		pthread_mutex_unlock(&philo->table->print);
	}
	return (tooken_forks);
}

void	release_fork(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->table->forks[philo->id
			% philo->table->args.number_of_philosophers]);
		pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
		pthread_mutex_lock(&philo->table->forks_status_mutex);
		philo->table->forks_status[philo->id
			% philo->table->args.number_of_philosophers] = 0;
		philo->table->forks_status[philo->id - 1] = 0;
		pthread_mutex_unlock(&philo->table->forks_status_mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->table->forks[philo->id
			% philo->table->args.number_of_philosophers]);
		pthread_mutex_lock(&philo->table->forks_status_mutex);
		philo->table->forks_status[philo->id - 1] = 0;
		philo->table->forks_status[philo->id
			% philo->table->args.number_of_philosophers] = 0;
		pthread_mutex_unlock(&philo->table->forks_status_mutex);
	}
}

static int	fork_lock(t_philosopher *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->table->args.number_of_philosophers;
	if (philo->table->args.number_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lld %d has taken a fork\n", ms_time(&philo->table->tv_start),
			philo->id);
		pthread_mutex_unlock(&philo->table->print);
		return (1);
	}
	else if (!philo->id % 2)
	{
		pthread_mutex_lock(&philo->table->forks[right_fork]);
		pthread_mutex_lock(&philo->table->forks[left_fork]);
		return (2);
	}
	pthread_mutex_lock(&philo->table->forks[left_fork]);
	pthread_mutex_lock(&philo->table->forks[right_fork]);
	return (2);
}
