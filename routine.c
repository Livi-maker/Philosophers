/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:07:41 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/14 18:07:44 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	try_to_eat(t_data *data, int id)
{
	int		fork_available;

	if (id == 0)
		fork_available = data->q;
	else
		fork_available = id - 1;
	pthread_mutex_lock(data->forks[id]->fork);
	pthread_mutex_lock(data->forks[fork_available]->fork);
	pthread_mutex_lock(data->print);
	printf("philo nr %d has taken a fork\n", id + 1);
	pthread_mutex_unlock(data->print);
	pthread_mutex_lock(data->print);
	printf("philo nr %d has taken a fork\n", id + 1);
	pthread_mutex_unlock(data->print);
	pthread_mutex_lock(data->print);
	printf("philo nr %d is eating\n\n", id + 1);
	pthread_mutex_unlock(data->print);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(data->forks[id]->fork);
	pthread_mutex_unlock(data->forks[fork_available]->fork);
}

void	thinking(t_data *data, int id)
{
	pthread_mutex_lock(data->print);
	printf("philo nr %d is thinking\n\n", id + 1);
	pthread_mutex_unlock(data->print);
}