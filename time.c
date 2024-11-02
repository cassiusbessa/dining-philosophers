#include "philo.h"

// static int	days_in_month(int month, int year);

// void legible_date(struct timeval *tv)
// {
//     int years = 1970;
//     int days = tv->tv_sec / 86400; // Total de dias desde a época Unix

//     // Calcular o número de anos
//     while (1)
//     {
// 			int days_in_year = (years % 4 == 0 && (years % 100 != 0 || years % 400 == 0)) ? 366 : 365;

// 			if (days < days_in_year)
// 				break; // Não há dias suficientes para avançar um ano

// 			days -= days_in_year;
// 			years++;
//     }
//     int months = 1;
//     while (days >= days_in_month(months, years))
//     {
// 			days -= days_in_month(months, years);
// 			months++;
//     }
//     int hours = (tv->tv_sec % 86400) / 3600;
//     int minutes = (tv->tv_sec % 3600) / 60;
//     int seconds = tv->tv_sec % 60;
//     printf("%d-%02d-%02d %02d:%02d:%02d\n", years, months, days + 1, hours, minutes, seconds);
// }

// static int	days_in_month(int month, int year)
// {
// 	int is_leap_year;

//     if (month < 1 || month > 12)
//         return -1;
//     is_leap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
//     if (month == 2)
// 		{
//       if (is_leap_year)
// 				return 29;
// 			else
// 				return 28;
//     } 
// 		else if (month == 4 || month == 6 || month == 9 || month == 11)
//       return 30;
//     else
//     	return 31;
// }

int	time_stamp_in_ms(struct timeval *start)
{
	struct timeval	tv;
	int				time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec - start->tv_sec) * 1000 + (tv.tv_usec - start->tv_usec) / 1000;
	return (time);
}

int	sleep_in_ms(int ms)
{
	return (usleep(ms * 1000));
}