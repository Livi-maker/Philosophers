/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 01:17:52 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/18 21:18:26 by ldei-sva         ###   ########.fr       */
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

typedef struct s_fork
{
	pthread_mutex_t	*fork;
	int				state;
}	t_fork;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				q;
	int				meals_eaten;
	long int		start;
	long int		eat_time;
}	t_philo;

typedef struct s_data
{
	struct s_fork	**forks;
	pthread_t		**philos;
	pthread_mutex_t	*print;
	pthread_mutex_t	*sleeping;
	pthread_mutex_t	*death;
	pthread_mutex_t	*variable;
	int				someone_died;
	int				min_meals;
	int				done_eating;
	int				q;
}	t_data;

void			create_philo(int q, t_data *data, char **av);
void			new_philo(pthread_t *thread, int q, t_data *data, char **av);
void			create_fork(int q, t_data *data);
struct s_fork	*new_mutex(pthread_mutex_t *mutex);
void			*routine(void *data);
int				try_to_eat(t_philo *philo, t_data *data, int id);
int				thinking(t_data *data, t_philo *philo);
long int		get_current_time(void);
long int		time_passed(long int time);
int				check_death(t_philo *philo, t_data *data);
int				check_death_sleeping(t_philo *philo, t_data *data);
int				sleeping(t_data *data, t_philo *philo, int id);
void			destroy_data(t_data *data);
void			destroy_philo(t_philo *philo);
void			check_forks(t_philo *philo);
void			eat(t_data *data, t_philo *philo, int id, int fork_available);
int				ft_atoi(const char *nptr);
#endif
