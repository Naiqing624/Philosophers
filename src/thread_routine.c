/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacao <nacao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:31:10 by naiqing           #+#    #+#             */
/*   Updated: 2025/02/24 09:38:11 by nacao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message("has right fork", philo, philo->philo_id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_message("has left fork", philo, philo->philo_id);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = true;
	pthread_mutex_unlock(philo->meal_lock);
	print_message("is eating", philo, philo->philo_id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = false;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->philo_id);
}

void	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->philo_id);
	ft_usleep(philo->time_to_sleep);
}

void	*routine_action(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

int	thread_creat(t_program *program, pthread_mutex_t *fork)
{
	pthread_t	monitoring_thread_id;
	int			i;

	if (pthread_create(&monitoring_thread_id, NULL, &monitor,
			program->philos) != 0)
		error_destory_all_mutex("Thread monitoring creat error", program, fork);
	i = 0;
	while (i < program->philos->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread_id, NULL,
				&routine_action, &program->philos[i]) != 0)
			error_destory_all_mutex("Thread creat error", program, fork);
		i++;
	}
	i = 0;
	if (pthread_join(monitoring_thread_id, NULL) != 0)
		error_destory_all_mutex("Thread monitoring join error", program, fork);
	while (i < program->philos->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread_id, NULL) != 0)
			error_destory_all_mutex("Thread join error", program, fork);
		i++;
	}
	return (0);
}
