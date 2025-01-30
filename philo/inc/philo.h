/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:38:59 by codespace         #+#    #+#             */
/*   Updated: 2025/01/30 17:35:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				num_eat;
	int				left_fork;
	int				right_fork;
	long long		last_eat;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	mutex_philo;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_must_eat;
	int				print_init;
	int				dead;
	int				ready;
	long long		start;
	t_philo			*philos;
	pthread_t		main;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}					t_data;

void		print_error(char *msg, t_data *data);
long long	get_ms(t_data *data);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
void		free_data(t_data *data);

void		init_structs(t_data *data);
void		init_routines(t_data *data);
void		set_data(t_data *data, int argc, char **argv);

void		*philo_life(void *philo);
void		*main_routine(void *arg);
void		wait_routines(t_data *data);

int			ft_sleep(t_philo *philo);
int			ft_eat(t_philo *philo);
void		print_status(t_philo *philo, char *status);
int			check_finish(t_philo *philo);
int			check_death(t_philo *philo);
int			philo_dead(t_data *data, int i);
void		start(t_data *data);
void		wait_philos(t_data *data);
void		init_forks(t_data *data);
int			everyone_ate(t_data *data);

#endif
