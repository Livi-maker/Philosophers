/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:40:56 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/18 21:23:30 by ldei-sva         ###   ########.fr       */
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

struct s_philo	*new_philo(pthread_t *thread, int id, t_data *data, char **av)
{
	t_philo	*philo;
	struct	timeval	*start;

	thread = calloc(1, sizeof(pthread_t));
	philo = calloc(1, sizeof(t_philo));
	philo->data = data;
	philo->id = id - 1;
	philo->meals_eaten = 0;
	pthread_mutex_lock(data->variable);
	philo->q = atoi(av[1]) - 1;
	philo->time_to_die = atoi(av[2]);
	philo->time_to_eat = atoi(av[3]);
 	philo->time_to_sleep = atoi(av[4]);
	pthread_mutex_unlock(data->variable);
	pthread_create(thread, NULL, routine, philo);
	data->philos[id - 1] = thread;
	return(philo);
}

void	create_philo(int q, t_data *data, char **av)
{
	t_philo		*philo;
	pthread_t	*thread;
	int			nr;

	nr = q;
	while (q > 0)
	{
		data->philos[q - 1] = calloc(1, sizeof(pthread_t));
		philo = new_philo(thread, q, data, av);
		q--;
	}
	while (nr >= 0)
	{
		pthread_join(*(data->philos[nr - 1]), NULL);
		nr--;
	}
}
