/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:03:36 by codespace         #+#    #+#             */
/*   Updated: 2025/01/31 13:16:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_structs(t_data *data)
{
	data->num_philos = 0;
	data->time_die = 0;
	data->time_eat = 0;
	data->time_sleep = 0;
	data->num_must_eat = -1;
	data->philos = NULL;
	data->forks = NULL;
	data->print_init = 0;
	data->dead = 0;
	data->ready = 0;
	data->main_init = 0;
	if (pthread_mutex_init(&data->print, NULL) != 0)
		print_error("Error: Mutex init error\n", data);
	else
		data->print_init = 1;
	if (pthread_mutex_init(&data->mutex_main, NULL) != 0)
		print_error("Error: Mutex init error\n", data);
	else
		data->main_init = 1;
}

void	init_forks(t_data *data)
{
	int	i;	

	data->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		print_error("Error: Malloc error\n", data);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			print_error("Error: Mutex init error\n", data);
		i++;
	}
}

void	thread_cases(t_data *data, t_philo *philo)
{
	if (data->num_philos == 1)
	{
		if (pthread_create(&philo->thread, NULL, case_one, (void *)philo))
			print_error("Error: Thread creation error\n", data);
	}
	else
	{
		if (pthread_create(&philo->thread, NULL, philo_life, (void *)philo))
			print_error("Error: Thread creation error\n", data);
	}
}

void	init_routines(t_data *data)
{
	int	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		print_error("Error: Malloc error\n", data);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->philos[i].mutex_philo, NULL) != 0)
			print_error("Error: Mutex init error\n", data);
		data->philos[i].id = i + 1;
		data->philos[i].dead = 0;
		data->philos[i].num_eat = 0;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].data = data;
		thread_cases(data, &data->philos[i]);
		i++;
	}
	if (pthread_create(&data->main, NULL, main_routine, (void *)data) != 0)
		print_error("Error: Thread creation error\n", data);
}

void	set_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_must_eat = ft_atoi(argv[5]);
	if (data->num_philos < 0 || data->num_philos > 200)
		print_error("Error: Invalid number of philosophers\n", data);
	if (data->time_die < 60 || data->time_eat < 60 || data->time_sleep < 60)
		print_error("Error: Invalid time\n", data);
	if (argc == 6 && data->num_must_eat < 0)
		print_error(
			"Error: Invalid num. of times each philosopher must eat\n", data);
	init_forks(data);
}
