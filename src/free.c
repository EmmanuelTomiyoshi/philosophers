/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:40:06 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/06 16:52:42 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	free_data(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_philos)
	{
		pthread_mutex_destroy(&d->forks[i]);
		pthread_mutex_destroy(&d->philos[i++].meal_lock);
	}
	pthread_mutex_destroy(&d->print.lock);
	pthread_mutex_destroy(&d->satisfied.lock);
	pthread_mutex_destroy(&d->dinner_is_over.lock);
	free(d->forks);
	free(d->philos);
	free(d);
}
