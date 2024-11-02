#include "philo.h"


int	main(int argc, char **argv)
{
	t_arguments	arguments;
	struct timeval	tv_start;

	gettimeofday(&tv_start, NULL);
	arguments = parser(argc, argv);
	if (arguments.error)
		return (1);
}