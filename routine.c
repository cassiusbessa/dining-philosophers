#include "philo.h"

void take_fork(t_philosopher *philo)
{
    int left_fork = philo->id - 1;
    int right_fork = (philo->id % philo->table->args.number_of_philosophers);

    if (philo->id % 2 == 0)  // Filósofos pares pegam o garfo direito primeiro
    {
        pthread_mutex_lock(&philo->table->forks[right_fork]);
        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d has taken a fork\n", time_stamp_in_ms(&philo->table->tv_start), philo->id);
        pthread_mutex_unlock(&philo->table->print);
        pthread_mutex_lock(&philo->table->forks[left_fork]);
        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d has taken a fork\n", time_stamp_in_ms(&philo->table->tv_start), philo->id);
        pthread_mutex_unlock(&philo->table->print);
    }
    else  // Filósofos ímpares pegam o garfo esquerdo primeiro
    {
        pthread_mutex_lock(&philo->table->forks[left_fork]);
        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d has taken a fork\n", time_stamp_in_ms(&philo->table->tv_start), philo->id);
        pthread_mutex_unlock(&philo->table->print);
        pthread_mutex_lock(&philo->table->forks[right_fork]);
        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d has taken a fork\n", time_stamp_in_ms(&philo->table->tv_start), philo->id);
        pthread_mutex_unlock(&philo->table->print);
    }
}

void *philosopher_routine(void *arg)
{
    t_philosopher *philo;
		
		philo = (t_philosopher *)arg;
    while (1)
    {
        take_fork(philo);
        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d is eating\n", time_stamp_in_ms(&philo->table->tv_start), philo->id);
        pthread_mutex_unlock(&philo->table->print);
        philo->last_meal_time = get_current_time_in_ms();
        philo->meals_eaten++;
        usleep(philo->table->args.time_to_eat * 1000);  // Simulando o tempo de comer
        pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
        pthread_mutex_unlock(&philo->table->forks[philo->id % philo->table->args.number_of_philosophers]);
        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d is sleeping\n", time_stamp_in_ms(&philo->table->tv_start), philo->id);
        pthread_mutex_unlock(&philo->table->print);
        usleep(philo->table->args.time_to_sleep * 1000);  // Simulando o tempo de dormir

        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d is thinking\n", time_stamp_in_ms(&philo->table->tv_start), philo->id);
        pthread_mutex_unlock(&philo->table->print);
    }
    return NULL;
}
