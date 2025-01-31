/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:54:48 by codespace         #+#    #+#             */
/*   Updated: 2025/01/31 13:18:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	start(t_data *data)
{
	struct timeval	t;

	pthread_mutex_lock(&data->mutex_main);
	data->ready = 1;
	gettimeofday(&t, NULL);
	data->start = t.tv_sec * 1000 + t.tv_usec / 1000;
	pthread_mutex_unlock(&data->mutex_main);
}

void	split_usleep(t_philo *philo, long long time)
{
	long long	start;

	start = get_ms(philo->data);
	while (get_ms(philo->data) - start < time)
		usleep(100);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	if (check_finish(philo))
		return (1);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (check_finish(philo))
		return (1);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->mutex_philo);
	philo->last_eat = get_ms(philo->data);
	pthread_mutex_unlock(&philo->mutex_philo);
	split_usleep(philo, philo->data->time_eat);
	if (check_finish(philo))
	{
		unlock_forks(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->mutex_philo);
	philo->num_eat++;
	pthread_mutex_unlock(&philo->mutex_philo);
	unlock_forks(philo);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (check_finish(philo))
		return (1);
	print_status(philo, "is sleeping");
	split_usleep(philo, philo->data->time_sleep);
	return (0);
}
