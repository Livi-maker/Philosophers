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
	pthread_t	*philo;
	int			id;
} t_philo;

typedef struct s_data
{
	struct s_fork	**forks;
	struct s_philo	**philos;
} t_data;

#endif
