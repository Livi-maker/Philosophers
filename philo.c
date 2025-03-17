/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:20:47 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/17 12:53:47 by ldei-sva         ###   ########.fr       */
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
	check_death(philo, data);
	if ((id % 2) == 0)
	{
		thinking(data, philo);
	}
	check_death(philo, data);
	try_to_eat(philo, data, id);
	check_death(philo, data);
	pthread_mutex_lock(data->print);
	printf("%.3ld %d is sleeping\n\n", time_passed(philo->start_time), id + 1);
	pthread_mutex_unlock(data->print);
	check_death_sleeping(philo, data);
	usleep(data->time_to_sleep * 1000);
	check_death(philo, data);
	if ((id % 2) == 1)
	{
		thinking(data, philo);
	}
	check_death(philo, data);
	routine(arg);
	return (NULL);
}

void	set_data(t_data	*data, char **av, int q)
{
	pthread_mutex_t	*print;

	print = malloc(sizeof(pthread_mutex_t));
	data->q = q - 1;
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
 	data->time_to_sleep = atoi(av[4]);
 	data->someone_died = 0;
	data->print = print;
}

int main(int ac, char **av)
{
	t_data			*data;
	int				q;
	pthread_mutex_t	*print;

	data = calloc(1, sizeof(t_data));
	if (ac < 5)
	{
		write(2, "Too few arguments\n", 18);
		return (0);
	}
	q = atoi(av[1]);
	set_data(data, av, q);
	create_fork(q, data);
	create_philo(q, data);
	while(data->someone_died == 0)
	{}
	exit(1);
}
