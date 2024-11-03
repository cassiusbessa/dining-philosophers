#include "philo.h"


int	main(int argc, char **argv)
{
	t_arguments	arguments;
	t_table					table;
	t_philosopher		*philosophers;
	int							i;

	arguments = parser(argc, argv);
	if (arguments.error)
		return (1);
	init_table(&table, arguments);
	philosophers = malloc(sizeof(t_philosopher) * arguments.number_of_philosophers);
	if (!philosophers)
	{
		destroy_table(&table);
		return (1);
	}
	init_philosophers(philosophers, &table);
	i = 0;
	gettimeofday(&table.tv_start, NULL);
	while (i < arguments.number_of_philosophers)
	{
		if (pthread_create(&philosophers[i].thread, NULL, philosopher_routine, &philosophers[i]))
		{
			while (--i >= 0)
      	pthread_join(philosophers[i].thread, NULL);
			destroy_table(&table);
			free(philosophers);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < arguments.number_of_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
	destroy_table(&table);
	free(philosophers);
}