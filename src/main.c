/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacao <nacao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:00:26 by nacao             #+#    #+#             */
/*   Updated: 2025/02/27 09:11:59 by nacao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_all_number(char	*argv)
{
	while (*argv != '\0')
	{
		if (*argv < '0' && *argv > '9')
			return (false);
		argv++;
	}
	return (true);
}

int	check_argv(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| is_all_number(argv[1]) == false)
		return (write(2, "Invalide Philo Number\n", 22), 1);
	if (ft_atoi(argv[2]) <= 0 || is_all_number(argv[2]) == false)
		return (write(2, "Invalide time_to_die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || is_all_number(argv[3]) == false)
		return (write(2, "Invalide time_to_eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || is_all_number(argv[4]) == false)
		return (write(2, "Invalide time_to_sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || is_all_number(argv[5]) == false))
		return (write(2, "Invalide number_of_times_each_philosopher_must_eat\n",
				51), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			philo[PHILO_MAX];
	t_program		program;
	pthread_mutex_t	fork[PHILO_MAX];

	if (argc != 6 && argc != 5)
		return (write(2, "Wrong arg count\n", 16), 1);
	if (check_argv(argv) == 1)
		return (1);
	init_program(philo, &program);
	init_fork(fork, ft_atoi(argv[1]));
	init_philo(philo, &program, fork, argv);
	thread_creat(&program, fork);
	error_destory_all_mutex(NULL, &program, fork);
	return (0);
}
