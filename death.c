/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:59:04 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/20 18:59:06 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_sleeping(t_philo *philo, t_data *data)
{
	if ((time_passed(philo->eat_time) + philo->time_to_sleep) \
	>= philo->time_to_die)
	{
		while (check_death(philo, data) == 0)
			;
		return (1);
	}
	return (0);
}

int	check_ifothers_died(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(data->death);
	pthread_mutex_lock(data->variable);
	if (data->someone_died == 1 || data->done_eating == 0)
	{
		pthread_mutex_unlock(data->death);
		pthread_mutex_unlock(data->variable);
		check_forks(philo);
		destroy_philo(philo);
		return (1);
	}
	pthread_mutex_unlock(data->death);
	pthread_mutex_unlock(data->variable);
	return (0);
}

int	check_death(t_philo *philo, t_data *data)
{
	if (check_ifothers_died(philo, data) == 1)
		return (1);
	if (time_passed(philo->eat_time) >= philo->time_to_die)
	{
		pthread_mutex_lock(data->variable);
		if (data->someone_died == 0)
		{
			data->someone_died = 1;
			pthread_mutex_unlock(data->variable);
			pthread_mutex_lock(data->print);
			printf("%ld %d died\n", time_passed(philo->start), \
			(philo->id) + 1);
			pthread_mutex_unlock(data->print);
			check_forks(philo);
			destroy_philo(philo);
			return (1);
		}
		pthread_mutex_unlock(data->variable);
	}
	return (0);
}
