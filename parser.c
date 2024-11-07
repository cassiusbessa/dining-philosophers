/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caqueiro <caqueiro@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:54:36 by caqueiro           #+#    #+#             */
/*   Updated: 2024/11/07 11:54:38 by caqueiro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return ((int)(nbr * sign));
}

static int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	check_arguments(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (-1);
	}
	if (!is_number(argv[1]) || !is_number(argv[2]) || !is_number(argv[3])
		|| !is_number(argv[4]) || (argc == 6 && !is_number(argv[5]))
		|| ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 0
		|| ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0
		|| (argc == 6 && ft_atoi(argv[5]) < 0))
	{
		printf("Error: wrong arguments\n");
		return (-1);
	}
	return (1);
}

t_arguments	parser(int argc, char **argv)
{
	t_arguments	arguments;

	arguments.error = 0;
	if (check_arguments(argc, argv) == -1)
	{
		arguments.error = 1;
		return (arguments);
	}
	arguments.number_of_philosophers = ft_atoi(argv[1]);
	arguments.time_to_die = ft_atoi(argv[2]);
	arguments.time_to_eat = ft_atoi(argv[3]);
	arguments.time_to_sleep = ft_atoi(argv[4]);
	arguments.max_philo_eat = 0;
	if (argc == 6)
		arguments.max_philo_eat = ft_atoi(argv[5]);
	else
		arguments.max_philo_eat = -1;
	return (arguments);
}
