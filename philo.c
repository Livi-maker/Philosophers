/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:20:47 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/14 14:40:28 by ldei-sva         ###   ########.fr       */
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
	if ((id % 2) == 0)
	{
		thinking(data, id);
	}
	try_to_eat(data, id);
	pthread_mutex_lock(data->print);
	printf("philo nr %d is sleeping\n\n", id + 1);
	pthread_mutex_unlock(data->print);
	usleep(data->time_to_sleep * 1000);
	if ((id % 2) == 1)
	{
		thinking(data, id);
	}
	routine(arg);
	return (NULL);
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
	print = malloc(sizeof(pthread_mutex_t));
	q = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	data->someone_died = 0;
	data->q = q - 1;
	data->print = print;
	create_fork(q, data);
	create_philo(q, data);
	while(data->someone_died == 0)
	{}
	exit(1);
}
