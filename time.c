/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <ldei-sva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:48:47 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/03/18 14:24:11 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time() 
{
    struct timeval	now;

    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

long int	time_passed(long int time)
{
	long int	now;
	long int	time_passed;

	now = get_current_time();
	time_passed = now - time;
	return (time_passed);
}
