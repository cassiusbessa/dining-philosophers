#include "philo.h"

int					starvation_calculator(t_table *table, t_philosopher *philo);
static int	all_philos_max_meals_eaten(t_table *table, t_philosopher *philos);

int	monitor(t_table *table, t_philosopher *philos)
{
	int	i;
	int	dead;

	while (1)
	{
		i = 0;
		dead = 0;
		while (i < table->args.number_of_philosophers)
		{
			dead = starvation_calculator(table, &philos[i]);
			if (dead)
			{
				pthread_mutex_lock(&table->print);
				printf("%lld %d died because last meals as eaten at %lld\n", time_stamp_in_ms(&table->tv_start), dead, philos[i].last_meal_time);
				pthread_mutex_unlock(&table->print);
				return (dead);
			}
			if (table->args.number_of_times_each_philosopher_must_eat > 0)
				dead = all_philos_max_meals_eaten(table, philos);
			if (dead)
			{
				pthread_mutex_lock(&table->dead_mutex);
				table->dead_flag = 1;
				pthread_mutex_unlock(&table->dead_mutex);
				pthread_mutex_lock(&table->print);
				printf("All philosophers have eaten %d times\n", table->args.number_of_times_each_philosopher_must_eat);
				pthread_mutex_unlock(&table->print);
				return (dead);
			}
			i++;
		}
		if (dead)
			return (1);
	}
	return (0);
}

int	starvation_calculator(t_table *table, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (((long long)table->args.time_to_die) + 1 < (time_stamp_in_ms(&table->tv_start) - philo->last_meal_time))
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_lock(&table->dead_mutex);
		table->dead_flag = 1;
		pthread_mutex_unlock(&table->dead_mutex);
		return (philo->id);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

static int	all_philos_max_meals_eaten(t_table *table, t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < table->args.number_of_philosophers)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		if (philos[i].meals_eaten < table->args.number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_unlock(&philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].meal_mutex);
		i++;
	}
	return (1);
}