/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:10:30 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/20 19:10:32 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->q)
	{
		pthread_mutex_destroy(data->forks[i]->fork);
		free(data->forks[i]->fork);
		free(data->forks[i]);
		free(data->philos[i]);
		i++;
	}
	pthread_mutex_destroy(data->print);
	pthread_mutex_destroy(data->death);
	pthread_mutex_destroy(data->variable);
	free(data->forks);
	free(data->philos);
	free(data->print);
	free(data->death);
	free(data->variable);
	free(data);
}

void	destroy_philo(t_philo *philo)
{
	if (philo)
		free(philo);
}

void	check_forks(t_philo *philo)
{
	int	fork;

	if (philo->id == 0)
		fork = philo->q;
	else
		fork = (philo->id) - 1;
	pthread_mutex_lock(philo->data->forks[philo->id]->fork);
	if (philo->data->forks[philo->id]->state == 1)
	{
		pthread_mutex_lock(philo->data->variable);
		philo->data->forks[philo->id]->state = 0;
		pthread_mutex_unlock(philo->data->variable);
	}
	pthread_mutex_unlock(philo->data->forks[philo->id]->fork);
	pthread_mutex_lock(philo->data->forks[fork]->fork);
	if (philo->data->forks[fork]->state == 1)
	{
		pthread_mutex_lock(philo->data->variable);
		philo->data->forks[philo->id]->state = 0;
		pthread_mutex_unlock(philo->data->variable);
	}
	pthread_mutex_unlock(philo->data->forks[fork]->fork);
}
