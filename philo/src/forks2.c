/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bherranz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:11:45 by bherranz          #+#    #+#             */
/*   Updated: 2025/02/06 15:11:46 by bherranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->current);
	pthread_mutex_unlock(&philo->right_fork->current);
}
