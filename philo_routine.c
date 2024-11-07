/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:58:44 by caqueiro          #+#    #+#             */
/*   Updated: 2024/11/07 20:33:42 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			has_death(t_table *table, t_philosopher *philo);
static void	think(t_philosopher *philo, int *thinking);
static void	sleep_routine(t_philosopher *philo);
static int	take_fork(t_philosopher *philo);
static int	release_fork(t_philosopher *philo);

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
		take_fork(philo);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->forks_status_mutex);
		return (0);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	int				thinking;
	long long		eating_time;

	philo = (t_philosopher *)arg;
	thinking = 0;
	while (!has_death(philo->table, philo)
		&& (philo->meals_eaten < philo->table->args.max_philo_eat
			|| philo->table->args.max_philo_eat == -1) && 1)
	{
		if (try_take_forks(philo))
		{
			thinking = 0;
			pthread_mutex_lock(&philo->meal_mutex);
			philo->last_meal_time = ms_time(&philo->table->tv_start);
			philo->meals_eaten++;
			pthread_mutex_unlock(&philo->meal_mutex);
			pthread_mutex_lock(&philo->table->print);
			printf("%lld %d is eating\n",
				ms_time(&philo->table->tv_start), philo->id);
			pthread_mutex_unlock(&philo->table->print);
			smart_sleep(philo->table->args.time_to_eat, &philo->table->tv_start,
				philo);
			release_fork(philo);
			sleep_routine(philo);
			if (!has_death(philo->table, philo) && !thinking)
				think(philo, &thinking);
		}
		else
			think(philo, &thinking);
	}
	return (NULL);
}

int	has_death(t_table *table, t_philosopher *philo)
{
	pthread_mutex_lock(&table->dead_mutex);
	if (table->dead_flag)
	{
		pthread_mutex_unlock(&table->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->dead_mutex);
	return (0);
}

static void	think(t_philosopher *philo, int *thinking)
{
	if (!has_death(philo->table, philo) && !*thinking)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lld %d is thinking\n",
			ms_time(&philo->table->tv_start), philo->id);
		pthread_mutex_unlock(&philo->table->print);
		smart_sleep(3, &philo->table->tv_start, philo);
		*thinking = 1;
	}
}

static void	sleep_routine(t_philosopher *philo)
{
	if (!has_death(philo->table, philo))
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lld %d is sleeping\n",
			ms_time(&philo->table->tv_start), philo->id);
		pthread_mutex_unlock(&philo->table->print);
		smart_sleep(philo->table->args.time_to_sleep, &philo->table->tv_start,
			philo);
	}
}

static int	take_fork(t_philosopher *philo)
{
	int left_fork;
	int right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->table->args.number_of_philosophers;
	if (!philo->id % 2)
	{
		pthread_mutex_lock(&philo->table->forks[right_fork]);
		pthread_mutex_lock(&philo->table->forks[left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[left_fork]);
		pthread_mutex_lock(&philo->table->forks[right_fork]);
	}
	if (!has_death(philo->table, philo))
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lld %d has taken a fork\n",
			ms_time(&philo->table->tv_start), philo->id);
		printf("%lld %d has taken a fork\n",
			ms_time(&philo->table->tv_start), philo->id);
		pthread_mutex_unlock(&philo->table->print);
	}
}

static int	release_fork(t_philosopher *philo)
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