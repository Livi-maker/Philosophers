/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:20:47 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/18 15:37:04 by ldei-sva         ###   ########.fr       */
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
	sleeping(data, philo, id);
	check_death(philo, data);
	if ((id % 2) == 1)
	{
		thinking(data, philo);
	}
	check_death(philo, data);
	routine(arg);
	return (NULL);
}

void	set_data(t_data	*data)
{
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
	pthread_mutex_t	*variable;

	print = malloc(sizeof(pthread_mutex_t));
	death = calloc(1, sizeof(pthread_mutex_t));
	variable = calloc(1, sizeof(pthread_mutex_t));
 	data->someone_died = 0;
	data->print = print;
	data->death = death;
	data->variable = variable;
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
	else if (ac == 6)
		data->min_meals = atoi(av[5]);
	else if (ac == 5)
		data->min_meals = -1;
	q = atoi(av[1]);
	set_data(data);
	create_fork(q, data);
	create_philo(q, data, av);
	while (data->someone_died == 0)
		;
	exit(1);
}
