/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:51:20 by bherranz          #+#    #+#             */
/*   Updated: 2025/02/03 21:26:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_forks(t_forks *file_list)
{
	t_forks	*temp;

	while (file_list)
	{
		temp = file_list;
		file_list = file_list->next;
		pthread_mutex_destroy(&temp->current);
		free(temp);
	}
}

t_forks	*ft_lstnew(int i)
{
	t_forks	*new_node;

	new_node = (t_forks *)malloc(sizeof(t_forks));
	if (!new_node)
		return (NULL);
	if (pthread_mutex_init(&new_node->current, NULL) != 0)
		print_error("Error: Mutex init error\n", NULL);
	new_node ->index = i;
	new_node ->next = NULL;
	return (new_node);
}

t_forks	*ft_lstlast(t_forks *lst)
{
	if (!lst)
		return (NULL);
	while (lst ->next)
		lst = lst ->next;
	return (lst);
}

void	ft_lstadd_back(t_forks **lst, t_forks *new)
{
	t_forks	*last;

	if (!lst || !new)
		return ;
	last = ft_lstlast(*lst);
	if (last)
		last ->next = new;
	else
		*lst = new;
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		ft_lstadd_back(&data->forks, ft_lstnew(i));
		i++;
	}
}
