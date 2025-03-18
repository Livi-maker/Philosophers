/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:17:52 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/18 20:02:24 by ldei-sva         ###   ########.fr       */
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
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				q;
	int				min_meals;
	struct s_data	*data;
	long int		start_time;
	long int		eat_time;
} t_philo;

typedef struct s_data
{
	struct s_fork	**forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*sleeping;
	pthread_mutex_t	*death;
	pthread_mutex_t	*variable;
	int				someone_died;
	int				min_meals;
} t_data;

void			create_philo(int q, t_data *data, char **av);
struct s_philo	*new_philo(pthread_t *thread, int q, t_data *data, char **av);
void			create_fork(int q, t_data *data);
struct s_fork	*new_mutex(pthread_mutex_t *mutex);
void			*routine(void *data);
void			try_to_eat(t_philo *philo, t_data *data, int id);
void			thinking(t_data *data, t_philo *philo);
long int    	get_current_time();
long int		time_passed(long int time);
void			check_death(t_philo *philo, t_data *data);
void			check_death_sleeping(t_philo *philo, t_data *data);
void			sleeping(t_data *data, t_philo *philo, int id);
void			check_death_eating(t_philo *philo, t_data *data);

#endif
