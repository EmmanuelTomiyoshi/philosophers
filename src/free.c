/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:40:06 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/03 10:07:41 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	free_data(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->number_of_philos)
		pthread_mutex_destroy(&d->forks[i++]);
	pthread_mutex_destroy(&d->print_lock);
	pthread_mutex_destroy(&d->lock_meal);
	free(d->forks);
	free(d->philos);
	free(d);
}
