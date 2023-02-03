/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:40:06 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/03 13:08:02 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->number_of_philos)
		pthread_mutex_destroy(&d->forks[i++]);
	pthread_mutex_destroy(&d->print.lock);
	pthread_mutex_destroy(&d->satisfied.lock);
	pthread_mutex_destroy(&d->dinner_is_over.lock);
	free(d->forks);
	free(d->philos);
	free(d);
}
