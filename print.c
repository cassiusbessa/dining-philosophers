#include "philo.h"

void	print_args(t_arguments args)
{
	printf("number_of_philosophers: %d\n", args.number_of_philosophers);
	printf("time_to_die: %d\n", args.time_to_die);
	printf("time_to_eat: %d\n", args.time_to_eat);
	printf("time_to_sleep: %d\n", args.time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat: %d\n", args.number_of_times_each_philosopher_must_eat);
}