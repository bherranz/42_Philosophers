/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:54:48 by codespace         #+#    #+#             */
/*   Updated: 2025/02/03 23:16:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	split_usleep(t_philo *philo, long long time)
{
	long long	start;

	start = get_ms(philo->data);
	while (get_ms(philo->data) - start < time)
		usleep(100);
}

void	exact_usleep(t_philo *philo, long long time)
{
	int			time_left;
	long long	start;

	start = get_ms(philo->data);
	pthread_mutex_lock(&philo->mutex_philo);
	time_left = (philo->data->time_die - (start - philo->last_eat));
	pthread_mutex_unlock(&philo->mutex_philo);
	if (time_left <= 0)
		time_left = 0;
	if (time_left < time)
		split_usleep(philo, time_left + 1);
	else
		split_usleep(philo, time);
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->current);
	if (check_finish(philo))
		return (pthread_mutex_unlock(&philo->left_fork->current), 1);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->current);
	if (check_finish(philo))
		return (unlock_forks(philo), 1);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->mutex_philo);
	philo->last_eat = get_ms(philo->data);
	pthread_mutex_unlock(&philo->mutex_philo);
	print_status(philo, "is eating");
	exact_usleep(philo, philo->data->time_eat);
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
	exact_usleep(philo, philo->data->time_sleep);
	return (0);
}

int	ft_think(t_philo *philo)
{
	int		time_left;
	int		left_eat_time_prev;
	t_data	*d;

	if (check_finish(philo))
		return (1);
	pthread_mutex_lock(&philo->mutex_philo);
	d = philo->data;
	pthread_mutex_unlock(&philo->mutex_philo);
	print_status(philo, "is thinking");
	pthread_mutex_lock(&philo->mutex_philo);
	time_left = d->time_die - (d->time_eat + d->time_sleep);
	left_eat_time_prev = d->time_eat - d->time_sleep;
	if (time_left > 0 && left_eat_time_prev > time_left)
		usleep((time_left + 1) * 1000);
	pthread_mutex_unlock(&philo->mutex_philo);
	return (0);
}
