#include "philo.h"


int	init_table(t_table *table, t_arguments args)
{
	int	i;

	table->args = args;
	table->forks = malloc(sizeof(pthread_mutex_t) * args.number_of_philosophers);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			while (i > 0)
				pthread_mutex_destroy(&table->forks[i--]);
			free(table->forks);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&table->print, NULL))
		return (1);
	if (pthread_mutex_init(&table->dead, NULL))
		return (1);
	gettimeofday(&table->tv_start, NULL);
	return (0);
}

int	init_philosophers(t_philosopher *philosophers, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->args.number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].meals_eaten = 0;
		philosophers[i].last_meal_time = 0;
		philosophers[i].table = table;
		i++;
	}
	return (0);
}

void	destroy_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->args.number_of_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->dead);
	free(table->forks);
}