/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacao <nacao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:00:26 by nacao             #+#    #+#             */
/*   Updated: 2025/02/17 16:58:55 by nacao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_all_number(char	*argv)
{
	while (*argv)
	{
		if (*argv < '0' && *argv > '9')
			return (false);
		argv++;
	}
	return (true);
}

bool	check_argv(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| !is_all_number(argv[1]))
		return (write(2, "Invalide Philo Number\n", 22), false);
	if (ft_atoi(argv[2]) <= 0 || !is_all_number(argv[2]))
		return (write(2, "Invalide time_to_die\n", 21), false);
	if (ft_atoi(argv[3]) <= 0 || !is_all_number(argv[3]))
		return (write(2, "Invalide time_to_eat\n", 21), false);
	if (ft_atoi(argv[4]) <= 0 || !is_all_number(argv[4]))
		return (write(2, "Invalide time_to_sleep\n", 23), false);
	if (argv[5] || ft_atoi(argv[5]) <= 0 || !is_all_number(argv[5]))
		return (write(2, "Invalide number_of_times_each_philosopher_must_eat\n", 51), false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo			philo[PHILO_MAX];
	t_program		program;
	pthread_mutex_t	*fork;
	
	if (argc != 6 && argc != 5)
		return (write(2, "Wrong arg count", 15), 1);
	if (!check_argv(argv))
		return (1);
	init_program(philo, &program);
	init_fork(fork, argc);
	init_philo(philo, &program, fork, argv);
}