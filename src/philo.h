/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacao <nacao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:00:46 by nacao             #+#    #+#             */
/*   Updated: 2025/02/24 09:40:53 by nacao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h> 
# include <stdbool.h>

# define PHILO_MAX	200

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_id;
	int				meals_eaten;
	int				num_of_philos;
	int				num_times_to_eat;
	bool			*dead;
	bool			eating;
	size_t			last_meal_time;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			time_to_eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	bool			dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
}					t_program;

//utils
int		ft_atoi(const char *str);
size_t	get_current_time(void);
void	error_destory_all_mutex(char *str, t_program *program,
			pthread_mutex_t *fork);
int		ft_usleep(size_t target_time_to_sleep);
int		dead_loop(t_philo *philo);
void	print_message(char *str, t_philo *philo, int philo_id);

//initialization
void	init_program(t_philo *philo, t_program *program);
void	init_fork(pthread_mutex_t *fork, int philo_num);
void	init_input(t_philo *philo, char	**argv);
void	init_philo(t_philo *philo, t_program *program,
			pthread_mutex_t *fork, char	**argv);

//monitor
void	*monitor(void *pointer);

void	*routine_action(void *pointer);

int		thread_creat(t_program *program, pthread_mutex_t *fork);

#endif