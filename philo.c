/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:20:47 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/14 12:02:48 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	printf("%s\n", "philo is sleeping");
	usleep(2000000);
	printf("%s\n", "philo was created");
}

struct s_fork	*new_struct(pthread_mutex_t *mutex)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	fork->fork = mutex;
	fork->state = 0;
	return(fork);
}

void	create_fork(int q, t_data *data)
{
	t_fork				**forks;
	t_fork				*fork;
	pthread_mutex_t		*mutex;

	forks = malloc(sizeof(t_fork *));
	while (q > 0)
	{
		pthread_mutex_init(mutex, NULL);
		fork = new_struct(mutex);
		forks[q] = fork;
		printf("fork n %d was created\n", q);
		q--;
	}
	data->forks = forks;
}

struct s_philo	*new_philo(pthread_t *thread, int q)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->philo = thread;
	philo->id = q;
}

void	create_philo(int q, t_data *data)
{
	t_philo		**philos;
	t_philo		*philo;
	pthread_t	*thread;

	philos = malloc(q * (sizeof(t_philo *)));
	while (q > 0)
	{
		pthread_create(thread, NULL, routine, data);
		philo = new_philo(thread, q);
		philos[q] = philo;
		q--;
		pthread_join(*thread, NULL);
	}
}

int main(int ac, char **av)
{
	t_data			*data;
	int				q;

	data = malloc(sizeof(t_data));
	if (ac < 5)
	{
		write(2, "Too few arguments\n", 18);
		return (0);
	}
	q = atoi(av[1]);
	create_fork(q, data);
	create_philo(q, data);
}
