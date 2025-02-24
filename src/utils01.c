/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naiqing <naiqing@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:28:36 by naiqing           #+#    #+#             */
/*   Updated: 2025/02/23 18:23:48 by naiqing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == true)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

// void	print_message(char *str, t_philo *philo, int philo_id)
// {
// 	size_t	time;
	
// 	pthread_mutex_lock(philo->write_lock);
// 	if (dead(philo) == 0)
// 	{
// 		time = get_current_time() - philo->start_time;
// 		printf("%zu %d %s\n", time, philo_id, str);
// 	}
// 	pthread_mutex_unlock(philo->write_lock);
// }

void	print_message(char *str, t_philo *philo, int philo_id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, philo_id, str);
	pthread_mutex_unlock(philo->write_lock);
}