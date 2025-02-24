/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naiqing <naiqing@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:41:29 by naiqing           #+#    #+#             */
/*   Updated: 2025/02/23 18:30:34 by naiqing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo, size_t time_to_die)
{
	int	result;

	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal_time > time_to_die
		&& philo->eating == false)
		result = 1;
	else
		result = 0;
	pthread_mutex_unlock(philo->meal_lock);
	return (result);
}


int	philo_all_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		if (philo_dead(&philo[i], philo[i].time_to_die) != 0)
		{
			print_message("is died", philo, philo->philo_id);
			pthread_mutex_lock(philo->dead_lock);
			*philo->dead = true;
			pthread_mutex_unlock(philo->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	all_is_ate(t_philo *philo)
{
	int	i;
	int	num_philo_finish_eating;

	i = 0;
	num_philo_finish_eating = 0;
	if (philo[0].num_times_to_eat == -1)
		return (0);
	while (i < philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo[i].num_times_to_eat)
			num_philo_finish_eating++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (num_philo_finish_eating == philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = true;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
	{
		if (philo_all_dead(philo) == 1 || all_is_ate(philo) == 1)
			break ;
	}
	return (pointer);
}
