/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:47:51 by codespace         #+#    #+#             */
/*   Updated: 2025/02/03 23:13:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	everyone_ate(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->mutex_main);
	if (data->num_must_eat == -1)
		return (pthread_mutex_unlock(&data->mutex_main), 0);
	pthread_mutex_unlock(&data->mutex_main);
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].mutex_philo);
		pthread_mutex_lock(&data->mutex_main);
		if (data->philos[i].num_eat < data->num_must_eat)
		{
			pthread_mutex_unlock(&data->mutex_main);
			pthread_mutex_unlock(&data->philos[i].mutex_philo);
			return (0);
		}
		pthread_mutex_unlock(&data->mutex_main);
		pthread_mutex_unlock(&data->philos[i].mutex_philo);
		i++;
	}
	return (1);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->mutex_main);
	if (!philo->data->dead || ft_strcmp(status, "died") == 0)
	{
		pthread_mutex_unlock(&philo->data->mutex_main);
		printf("%lld %d %s\n", get_ms(philo->data), philo->id, status);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_main);
	pthread_mutex_unlock(&philo->data->print);
}

int	check_finish(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_main);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->mutex_main);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_main);
	pthread_mutex_lock(&philo->mutex_philo);
	if (philo->data->num_must_eat != -1
		&& philo->num_eat >= philo->data->num_must_eat)
	{
		pthread_mutex_unlock(&philo->mutex_philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex_philo);
	return (check_death(philo));
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_philo);
	if (get_ms(philo->data) - philo->last_eat > philo->data->time_die)
	{
		pthread_mutex_lock(&philo->data->mutex_main);
		if (!philo->data->dead && philo->data->num_philos != 1)
		{
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->mutex_main);
			print_status(philo, "died");
		}
		else
			pthread_mutex_unlock(&philo->data->mutex_main);
		pthread_mutex_unlock(&philo->mutex_philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex_philo);
	return (0);
}

int	philo_dead(t_data *data, int i)
{
	int	dead;

	pthread_mutex_lock(&data->philos[i].mutex_philo);
	dead = data->philos[i].dead;
	pthread_mutex_unlock(&data->philos[i].mutex_philo);
	return (dead);
}
