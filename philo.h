/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:17:52 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/14 11:55:05 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct	s_fork
{
	pthread_mutex_t	*fork;
	int				state;
} t_fork;

typedef struct	s_philo
{
	pthread_t		*philo;
	int				id;
	struct s_data	*data;
} t_philo;

typedef struct s_data
{
	struct s_fork	**forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*sleeping;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				someone_died;
	int				q;
} t_data;

void			create_philo(int q, t_data *data);
struct s_philo	*new_philo(pthread_t *thread, int q, t_data *data);
void			create_fork(int q, t_data *data);
struct s_fork	*new_mutex(pthread_mutex_t *mutex);
void			*routine(void *data);
void			try_to_eat(t_data *data, int id);
void			thinking(t_data *data, int id);

#endif
