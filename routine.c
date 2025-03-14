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

void	try_to_eat(t_data *data, int id, int fork_available)
{
	if ((data->forks[id])->state == 0 && data->forks[fork_available]->state == 0)
	{
		data->forks[id]->state = 1;
		data->forks[fork_available]->state = 1;
		pthread_mutex_lock(data->forks[id]->fork);
		pthread_mutex_lock(data->forks[fork_available]->fork);
		printf("philo nr %d has taken a fork\n", id + 1);
		printf("philo nr %d has taken a fork\n", id + 1);
		printf("philo nr %d is eating\n\n", id + 1);
		usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(data->forks[id]->fork);
		pthread_mutex_unlock(data->forks[fork_available]->fork);
		data->forks[id]->state = 0;
		data->forks[fork_available]->state = 0;
	}
}