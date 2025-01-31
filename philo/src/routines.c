/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:39:10 by codespace         #+#    #+#             */
/*   Updated: 2025/01/31 17:39:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_routines(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->main, NULL);
}

void	wait_philos(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->mutex_main);
		if (data->ready)
		{
			pthread_mutex_unlock(&data->mutex_main);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_main);
	}
}

void	*case_one(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	wait_philos(data);
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	usleep(data->time_die * 1000);
	pthread_mutex_lock(&philo->mutex_philo);
	philo->dead = 1;
	print_status(philo, "died");
	pthread_mutex_unlock(&philo->mutex_philo);
	return (NULL);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	wait_philos(data);
	pthread_mutex_lock(&philo->mutex_philo);
	philo->last_eat = get_ms(data);
	pthread_mutex_unlock(&philo->mutex_philo);
	if (philo->id % 2)
		usleep(philo->data->time_eat * 1000);
	while (!check_finish(philo))
	{
		if (ft_eat(philo))
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
		if (check_finish(philo))
			return (NULL);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	*main_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (!check_finish(data->philos))
	{
		while (i < data->num_philos)
		{
			if (philo_dead(data, i))
			{
				pthread_mutex_lock(&data->mutex_main);
				data->dead = 1;
				pthread_mutex_unlock(&data->mutex_main);
				return (NULL);
			}
			i++;
		}
		i = 0;
		if (everyone_ate(data))
			break ;
	}
	return (NULL);
}
