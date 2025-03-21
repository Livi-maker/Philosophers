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
	return (fork);
}

void	create_fork(int q, t_data *data)
{
	t_fork				**forks;
	pthread_mutex_t		*mutex;

	mutex = NULL;
	forks = calloc(q, sizeof(t_fork *));
	while (q > 0)
	{
		forks[q - 1] = new_mutex(mutex);
		q--;
	}
	data->forks = forks;
}

void	new_philo(pthread_t *thread, int id, t_data *data, char **av)
{
	t_philo			*philo;

	thread = calloc(1, sizeof(pthread_t));
	philo = calloc(1, sizeof(t_philo));
	philo->data = data;
	philo->id = id - 1;
	philo->meals_eaten = 0;
	pthread_mutex_lock(data->variable);
	philo->q = ft_atoi(av[1]) - 1;
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->start = get_current_time();
	philo->eat_time = philo->start;
	pthread_mutex_unlock(data->variable);
	pthread_create(thread, NULL, routine, philo);
	data->philos[id - 1] = thread;
}

void	create_philo(int q, t_data *data, char **av)
{
	pthread_t	*thread;
	int			nr;

	nr = q;
	thread = NULL;
	while (q > 0)
	{
		new_philo(thread, q, data, av);
		q--;
	}
	while (nr > 0)
	{
		pthread_join(*(data->philos[nr - 1]), NULL);
		nr--;
	}
}
