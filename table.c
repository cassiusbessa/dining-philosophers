#include "philo.h"

static int	init_forks_status(t_table *table, t_arguments args);
static int	init_forks_mutex(t_table *table, t_arguments args);

int	init_table(t_table *table, t_arguments args)
{
	table->args = args;
	table->dead_flag = 0;
	if (init_forks_status(table, args))
		return (1);
	if (init_forks_mutex(table, args))
		return (1);
	if (pthread_mutex_init(&table->print, NULL))
		return (1);
	if (pthread_mutex_init(&table->dead_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&table->forks_status_mutex, NULL))
		return (1);
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
		if (pthread_mutex_init(&philosophers[i].meal_mutex, NULL))
		{
			while (i > 0)
				pthread_mutex_destroy(&philosophers[i--].meal_mutex);
			return (1);
		} 
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
	pthread_mutex_destroy(&table->dead_mutex);
	pthread_mutex_destroy(&table->forks_status_mutex);
	free(table->forks);
	free(table->forks_status);
}

static int	init_forks_status(t_table *table, t_arguments args)
{
	int	i;
	table->forks_status = malloc(sizeof(int) * args.number_of_philosophers);
	if (!table->forks_status)
		return (1);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		table->forks_status[i] = 0;
		i++;
	}
	return (0);
}

static int	init_forks_mutex(t_table *table, t_arguments args)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * args.number_of_philosophers);
	if (!table->forks)
		return (-1);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			while (i > 0)
				pthread_mutex_destroy(&table->forks[i--]);
			free(table->forks);
			return (-1);
		}
		i++;
	}
	return (0);
}