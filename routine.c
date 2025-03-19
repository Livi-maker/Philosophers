/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:07:41 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/18 21:24:46 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_to_eat(t_philo *philo, t_data *data, int id)
{
	int		fork_available;

	if (id == 0)
		fork_available = philo->q;
	else
		fork_available = id - 1;
	/*pthread_mutex_lock(data->variable);
	if (data->forks[fork_available]->state == 1 || data->forks[id]->state == 1)
	{
		pthread_mutex_unlock(data->variable);
		return (0);
	}*/
	pthread_mutex_lock(data->forks[id]->fork);
	data->forks[id]->state = 1;
	if (data->forks[fork_available]->state == 1)
	{
		pthread_mutex_unlock(data->forks[id]->fork);
		data->forks[id]->state = 0;
		return (0);
	}
	pthread_mutex_lock(data->forks[fork_available]->fork);
	pthread_mutex_lock(data->variable);
	data->forks[fork_available]->state = 1;
	pthread_mutex_unlock(data->variable);
	pthread_mutex_lock(data->print);
	printf("%ld %d has taken a fork\n", time_passed(philo->start_time), id + 1);
	printf("%ld %d has taken a fork\n", time_passed(philo->start_time), id + 1);
	printf("%ld %d is eating\n\n", time_passed(philo->start_time), id + 1);
	pthread_mutex_unlock(data->print);
	philo->eat_time = get_current_time();
	usleep(philo->time_to_eat * 1000);
	philo->meals_eaten += 1;
	pthread_mutex_lock(data->variable);
	if (philo->meals_eaten == data->min_meals)
		data->done_eating -= 1;
	pthread_mutex_unlock(data->forks[id]->fork);
	pthread_mutex_unlock(data->forks[fork_available]->fork);
	data->forks[id]->state = 0;
	data->forks[fork_available]->state = 0;
	pthread_mutex_unlock(data->variable);
	return (1);
}

void	thinking(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(data->print);
	printf("%ld %d is thinking\n\n", time_passed(philo->start_time), (philo->id) + 1);
	pthread_mutex_unlock(data->print);
}

void	check_death_eating(t_philo *philo, t_data *data)
{
	if (philo->time_to_eat >= philo->time_to_die && (philo->id % 2) == 0)
	{
		while(1)
			check_death(philo, data);
	}
}

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
	if (data->someone_died == 1 || data->done_eating == 0)
	{
		pthread_mutex_unlock(data->death);
		exit(0);
	}
	pthread_mutex_unlock(data->death);
	if (time_passed(philo->eat_time) >= philo->time_to_die)
	{
		pthread_mutex_lock(data->death);
		if (data->someone_died == 0)
		{
			data->someone_died = 1;
			pthread_mutex_unlock(data->death);
			pthread_mutex_lock(data->print);
			printf("%ld %d has died\n", time_passed(philo->start_time), (philo->id) + 1);
			pthread_mutex_unlock(data->print);
			exit (1);
		}
		pthread_mutex_unlock(data->death);

 	}
}

void	sleeping(t_data *data, t_philo *philo, int id)
{
	pthread_mutex_lock(data->print);
	printf("%ld %d is sleeping\n\n", time_passed(philo->start_time), id + 1);
	pthread_mutex_unlock(data->print);
	check_death_sleeping(philo, data);
	usleep(philo->time_to_sleep * 1000);
}
