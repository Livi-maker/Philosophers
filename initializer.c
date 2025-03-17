/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:40:56 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/17 12:38:16 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct s_fork	*new_mutex(pthread_mutex_t *mutex)
{
	t_fork	*fork;

	mutex = calloc(1, sizeof(pthread_mutex_t));
	fork = calloc(1, sizeof(t_fork));
	pthread_mutex_init(mutex, NULL);
	fork->fork = mutex;
	fork->state = 0;
	return(fork);
}

void	create_fork(int q, t_data *data)
{
	t_fork				**forks;
	t_fork				*fork;
	pthread_mutex_t		*mutex;

	forks = calloc(q, sizeof(t_fork *));
	while (q > 0)
	{
		forks[q - 1] = new_mutex(mutex);
		q--;
	}
	data->forks = forks;
}

struct s_philo	*new_philo(pthread_t *thread, int q, t_data *data)
{
	t_philo	*philo;
	struct	timeval	*start;

	thread = calloc(1, sizeof(pthread_t));
	philo = calloc(1, sizeof(t_philo));
	philo->data = data;
	philo->id = q - 1;
	pthread_create(thread, NULL, routine, philo);
	philo->philo = thread;
	philo->start_time = get_current_time();
	philo->eat_time = philo->start_time;
	return(philo);
}

void	create_philo(int q, t_data *data)
{
	t_philo		*philo;
	pthread_t	*thread;

	while (q > 0)
	{

		philo = new_philo(thread, q, data);
		q--;
	}
}
