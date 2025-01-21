/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:38:45 by codespace         #+#    #+#             */
/*   Updated: 2025/01/21 15:06:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//Argmuentos: num_philos time_to_die time_to_eat time_to_sleep [num_each_philosopher_must_eat]

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (argc < 5 || argc > 6)
	{
		print_error("Error: Invalid number of arguments\n");
		return (1);
	}
	printf("Hello, Philo!\n");
	return (0);
}
