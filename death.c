#include "philo.h"

void	check_death_sleeping(t_philo *philo, t_data *data)
{
	if ((time_passed(philo->eat_time) + philo->time_to_sleep) >= philo->time_to_die)
	{
		while(1)
			check_death(philo, data);
	}
}

void	check_death(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->death);
	pthread_mutex_lock(data->variable);
	if (data->someone_died == 1 || data->done_eating == 0)
	{
		pthread_mutex_unlock(data->death);
		pthread_mutex_unlock(data->variable);
		check_forks(philo);
		destroy_philo(philo);
		exit(0);
	}
	pthread_mutex_unlock(data->death);
	pthread_mutex_unlock(data->variable);
	if (time_passed(philo->eat_time) >= philo->time_to_die)
	{
		pthread_mutex_lock(data->variable);
		if (data->someone_died == 0)
		{
			data->someone_died = 1;
			pthread_mutex_unlock(data->variable);
			pthread_mutex_lock(data->print);
			printf("%ld %d has died\n", time_passed(philo->start_time), (philo->id) + 1);
			pthread_mutex_unlock(data->print);
			check_forks(philo);
			destroy_philo(philo);
			exit (0);
		}
		pthread_mutex_unlock(data->variable);
 	}
}