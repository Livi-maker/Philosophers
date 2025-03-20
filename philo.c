/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:20:47 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/18 21:23:54 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_data(t_data	*data, int q)
{
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
	pthread_mutex_t	*variable;
	pthread_t	**philos;

	data->q = q;
	print = calloc(1, sizeof(pthread_mutex_t));
	death = calloc(1, sizeof(pthread_mutex_t));
	variable = calloc(1, sizeof(pthread_mutex_t));
	philos = calloc(q, sizeof(pthread_t *));
	pthread_mutex_init(print, NULL);
	pthread_mutex_init(death, NULL);
	pthread_mutex_init(variable, NULL);
 	data->someone_died = 0;
	data->print = print;
	data->death = death;
	data->variable = variable;
	data->done_eating = q;
	data->philos = philos;
}

int main(int ac, char **av)
{
	t_data			*data;
	int				q;

	if (ac < 5)
	{
		write(2, "Too few arguments\n", 18);
		return (0);
	}
	data = calloc(1, sizeof(t_data));
	if (ac >= 6)
		data->min_meals = atoi(av[5]);
	else
		data->min_meals = -1;
	q = atoi(av[1]);
	set_data(data, q);
	create_fork(q, data);
	create_philo(q, data, av);
	destroy_data(data);
}
