/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:39:10 by codespace         #+#    #+#             */
/*   Updated: 2025/01/30 18:05:26 by codespace        ###   ########.fr       */
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
		pthread_mutex_lock(&data->print);
		if (data->ready)
		{
			pthread_mutex_unlock(&data->print);
			break ;
		}
		pthread_mutex_unlock(&data->print);
	}
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
			break ;
		if (ft_sleep(philo))
			break ;
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
	while (1)
	{
		while (i < data->num_philos)
		{
			if (philo_dead(data, i))
				return (NULL) ;
			i++;
		}
		i = 0;
		if (everyone_ate(data))
			break ;
	}
	return (NULL);
}
