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

void	*routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		id;

	philo = (t_philo *)arg;
	data = philo->data;
	id = philo->id;
	while (1)
	{
		if ((id % 2) == 0 && thinking(data, philo) == 1)
			return (NULL);
		if ((id % 2) == 0)
			usleep(1);
		if (check_death(philo, data) == 1)
			return (NULL);
		while (try_to_eat(philo, data, id) == 0)
			if (check_death(philo, data) == 1)
				return (NULL);
		if (sleeping(data, philo, id))
			return (NULL);
		if ((id % 2) == 1)
			if (thinking(data, philo) == 1)
				return (NULL);
	}
	return (NULL);
}

int	try_to_eat(t_philo *philo, t_data *data, int id)
{
	int		fork_available;

	if (id == 0)
		fork_available = philo->q;
	else
		fork_available = id - 1;
	pthread_mutex_lock(data->variable);
	if (data->forks[fork_available]->state == 1 && data->forks[id]->state == 1)
	{
		pthread_mutex_unlock(data->variable);
		return (0);
	}
	pthread_mutex_unlock(data->variable);
	pthread_mutex_lock(data->forks[id]->fork);
	pthread_mutex_lock(data->variable);
	data->forks[id]->state = 1;
	pthread_mutex_unlock(data->variable);
	if (data->forks[fork_available]->state == 1)
	{
		pthread_mutex_unlock(data->forks[id]->fork);
		data->forks[id]->state = 0;
		return (0);
	}
	eat(data, philo, id, fork_available);
	return (1);
}

void	eat(t_data *data, t_philo *philo, int id, int fork_available)
{
	pthread_mutex_lock(data->forks[fork_available]->fork);
	pthread_mutex_lock(data->variable);
	data->forks[fork_available]->state = 1;
	if (data->someone_died == 0)
	{
		pthread_mutex_lock(data->print);
		printf("%ld %d has taken a fork\n", time_passed(philo->start), id + 1);
		printf("%ld %d has taken a fork\n", time_passed(philo->start), id + 1);
		printf("%ld %d is eating\n\n", time_passed(philo->start), id + 1);
		pthread_mutex_unlock(data->print);
	}
	pthread_mutex_unlock(data->variable);
	philo->eat_time = get_current_time();
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(data->variable);
	data->forks[id]->state = 0;
	data->forks[fork_available]->state = 0;
	pthread_mutex_unlock(data->forks[id]->fork);
	pthread_mutex_unlock(data->forks[fork_available]->fork);
	philo->meals_eaten += 1;
	if (philo->meals_eaten == data->min_meals)
		data->done_eating -= 1;
	pthread_mutex_unlock(data->variable);
}

int	thinking(t_data *data, t_philo *philo)
{
	if (check_death(philo, data) == 1)
		return (1);
	pthread_mutex_lock(data->print);
	printf("%ld %d is thinking\n\n", \
	time_passed(philo->start), (philo->id) + 1);
	pthread_mutex_unlock(data->print);
	return (0);
}

int	sleeping(t_data *data, t_philo *philo, int id)
{
	if (check_death(philo, data) == 1)
		return (1);
	pthread_mutex_lock(data->print);
	printf("%ld %d is sleeping\n\n", time_passed(philo->start), id + 1);
	pthread_mutex_unlock(data->print);
	if (check_death_sleeping(philo, data) == 1)
		return (1);
	usleep(philo->time_to_sleep * 1000);
	return (0);
}
