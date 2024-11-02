#include "philosophers.h"


int	main(int argc, char **argv)
{
	t_arguments	arguments;

	arguments = parser(argc, argv);
	if (arguments.error)
		return (1);
	print_args(arguments);
}