/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:11:44 by caqueiro          #+#    #+#             */
/*   Updated: 2024/11/07 23:12:20 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ms_time(struct timeval *start)
{
	struct timeval	tv;
	long long		now;
	long long		start_time;

	gettimeofday(&tv, NULL);
	now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	start_time = (start->tv_sec * 1000) + (start->tv_usec / 1000);
	return (now - start_time);
}

void	smart_sleep(long long interval_in_ms, struct timeval *start,
		t_philosopher *philo)
{
	long long	now;
	long long	target_time;

	now = ms_time(start);
	target_time = now + interval_in_ms;
	while (now < target_time)
	{
		usleep(200);
		now = ms_time(start);
	}
}
