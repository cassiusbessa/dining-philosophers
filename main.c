/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:13:54 by caqueiro          #+#    #+#             */
/*   Updated: 2024/11/07 23:13:57 by caqueiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philo_threads(t_philosopher *philosophers, t_table *table);

int	main(int argc, char **argv)
{
	t_arguments		arguments;
	t_table			table;
	t_philosopher	*philosophers;
	int				i;

	arguments = parser(argc, argv);
	if (arguments.error)
		return (1);
	init_table(&table, arguments);
	philosophers = malloc(sizeof(t_philosopher)
			* arguments.number_of_philosophers);
	if (!philosophers)
		return (destroy_table(&table), 1);
	init_philosophers(philosophers, &table);
	gettimeofday(&table.tv_start, NULL);
	if (create_philo_threads(philosophers, &table))
		return (1);
	monitor(&table, philosophers);
	i = 0;
	while (i < arguments.number_of_philosophers)
		pthread_join(philosophers[i++].thread, NULL);
	destroy_table(&table);
	free(philosophers);
}

static int	create_philo_threads(t_philosopher *philosophers, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->args.number_of_philosophers)
	{
		if (pthread_create(&philosophers[i].thread, NULL, philosopher_routine,
				&philosophers[i]))
		{
			while (--i >= 0)
				pthread_join(philosophers[i].thread, NULL);
			destroy_table(table);
			free(philosophers);
			return (1);
		}
		i++;
	}
	return (0);
}
