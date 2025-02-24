/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initia.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naiqing <naiqing@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:07:41 by nacao             #+#    #+#             */
/*   Updated: 2025/02/23 18:20:33 by naiqing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

void	init_input(t_philo *philo, char	**argv)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	init_fork(pthread_mutex_t *fork, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}	
}

void	init_philo(t_philo *philo, t_program *program,
					pthread_mutex_t *fork, char	**argv)
{
	int		i;
	size_t	start_time;

	i = 0;
	start_time = get_current_time();
	while (i < ft_atoi(argv[1]))
	{
		philo[i].philo_id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].eating = false;
		init_input(&philo[i], argv);
		philo[i].start_time = start_time;
		philo[i].last_meal_time = start_time;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].write_lock = &program->write_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].dead = &program->dead_flag;
		philo[i].left_fork = &fork[i];
		if (i == 0)
			philo[i].right_fork = &fork[philo[i].num_of_philos - 1];
		else
			philo[i].right_fork = &fork[i - 1];
		i++;
	}
}

void	init_program(t_philo *philo, t_program *program)
{
	program->dead_flag = false;
	program->philos = philo;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
