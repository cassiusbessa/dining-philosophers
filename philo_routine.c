/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:58:44 by caqueiro          #+#    #+#             */
/*   Updated: 2024/11/07 23:14:43 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			has_death(t_table *table, t_philosopher *philo);

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
			eat(philo);
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
