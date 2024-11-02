#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>

typedef struct s_arguments {
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	int	error;
} t_arguments;

t_arguments	parser(int argc, char **argv);
void	print_args(t_arguments args);

#endif
