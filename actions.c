/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:08:40 by caqueiro          #+#    #+#             */
/*   Updated: 2024/11/07 23:08:42 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philosopher *philo, int *thinking)
{
	if (!has_death(philo->table, philo) && !*thinking)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%lld %d is thinking\n",
			ms_time(&philo->table->tv_start), philo->id);
		pthread_mutex_unlock(&philo->table->print);
		smart_sleep(1, &philo->table->tv_start, philo);
		*thinking = 1;
	}
}

void	sleep_routine(t_philosopher *philo)
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

void	eat(t_philosopher *philo)
{
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
}
