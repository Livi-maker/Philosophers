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
	int		fork_available;

	philo = (t_philo *)arg;
	data = philo->data;
	id = philo->id;
	if (id == 0)
		fork_available = data->q;
	else
		fork_available = id - 1;
	pthread_mutex_lock(data->thinking);
	if ((id % 2) == 1)
		printf("philo nr %d is thinking\n\n", id + 1);
	pthread_mutex_unlock(data->thinking);
	while ((data->forks[id])->state == 1 || data->forks[fork_available]->state == 1)
	{}
	try_to_eat(data, id, fork_available);
	printf("philo nr %d is sleeping\n\n", id + 1);
	usleep(data->time_to_sleep * 1000);
	routine(arg);
	return (NULL);
}


int main(int ac, char **av)
{
	t_data	*data;
	int		q;
	pthread_mutex_t	*thinking;

	data = calloc(1, sizeof(t_data));
	if (ac < 5)
	{
		write(2, "Too few arguments\n", 18);
		return (0);
	}
	thinking = malloc(sizeof(pthread_mutex_t));
	q = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	data->someone_died = 0;
	data->q = q - 1;
	data->thinking = thinking;
	create_fork(q, data);
	create_philo(q, data);
	while(data->someone_died == 0)
	{}
	exit(1);
}
