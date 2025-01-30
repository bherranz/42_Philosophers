/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:38:45 by codespace         #+#    #+#             */
/*   Updated: 2025/01/30 16:04:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

//Argmuentos: num_philos time_to_die time_to_eat time_to_sleep [num_each_philosopher_must_eat]

int	main(int argc, char **argv)
{
	t_data	data;

	init_structs(&data);
	if (argc < 5 || argc > 6)
		print_error("Error: Invalid number of arguments\n", &data);
	set_data(&data, argc, argv);
	init_routines(&data);
	wait_routines(&data);
	free_data(&data);
	return (0);
}
