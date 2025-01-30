/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:06:23 by codespace         #+#    #+#             */
/*   Updated: 2025/01/30 21:57:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//usar después de inicializar los hilos
void	start(t_data *data)
{
	struct timeval	t;

	pthread_mutex_lock(&data->print);
	data->ready = 1;
	gettimeofday(&t, NULL);
	data->start = t.tv_sec * 1000 + t.tv_usec / 1000;
	pthread_mutex_unlock(&data->print);
}

void	print_error(char *msg, t_data *data)
{
	write(2, msg, ft_strlen(msg));
	free_data(data);
	exit(1);
}

long long	get_ms(t_data *data)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - data->start);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->forks)
		free(data->forks);
	if (data->philos)
	{
		while (data->num_philos)
		{
			data->num_philos--;
			//pthread_detach(data->philos[data->num_philos].thread);
			pthread_mutex_destroy(&data->philos[data->num_philos].mutex_philo);
		}
		free(data->philos);
	}
	if (data->print_init)
		pthread_mutex_destroy(&data->print);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	if (!s)
		return (0);
	while (s[count])
	{
		count++;
	}
	return (count);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	nb;

	neg = 0;
	nb = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = 1;
		str++;
	}
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	if (neg == 1)
		nb = -nb;
	return (nb);
}
