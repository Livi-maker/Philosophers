/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:07:41 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/17 12:52:58 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	try_to_eat(t_philo *philo, t_data *data, int id)
{
	int		fork_available;

	if (id == 0)
		fork_available = data->q;
	else
		fork_available = id - 1;
	pthread_mutex_lock(data->forks[id]->fork);
	pthread_mutex_lock(data->print);
	printf("%.3ld %d has taken a fork\n", time_passed(philo->start_time), id + 1);
 	pthread_mutex_unlock(data->print);
	while (data->q == 0)
		check_death(philo, data);
	pthread_mutex_lock(data->forks[fork_available]->fork);
	pthread_mutex_lock(data->print);
	printf("%.3ld %d has taken a fork\n", time_passed(philo->start_time), id + 1);
	printf("%.3ld %d is eating\n\n", time_passed(philo->start_time), id + 1);
	pthread_mutex_unlock(data->print);
	usleep(data->time_to_eat * 1000);
	philo->eat_time = get_current_time();
	pthread_mutex_unlock(data->forks[id]->fork);
	pthread_mutex_unlock(data->forks[fork_available]->fork);
}

void	thinking(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(data->print);
	printf("%.3ld %d is thinking\n\n", time_passed(philo->start_time), (philo->id) + 1);
	pthread_mutex_unlock(data->print);
}

void	check_death_sleeping(t_philo *philo, t_data *data)
{
	if ((philo->eat_time + data->time_to_sleep) >= data->time_to_die)
	{
		while(1)
			check_death(philo, data);
	}
}

void	check_death(t_philo *philo, t_data *data)
{
	if (time_passed(philo->eat_time) >= data->time_to_die)
	{
		printf("%.3ld %d has died\n", time_passed(philo->start_time), (philo->id) + 1);
		data->someone_died = 1;
 		exit (1);
 	}
}

