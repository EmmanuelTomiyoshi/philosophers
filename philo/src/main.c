/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:25:18 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/09 14:29:53 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_philos)
	{
		if (pthread_create(&d->philos[i].tid, NULL, routine,
				(void *)&d->philos[i]) != 0)
			return (-1);
		i++;
	}
	pthread_create(&d->monitor, NULL, monitor, (void *)d);
	i = 0;
	while (i < d->num_philos)
	{
		if (pthread_join(d->philos[i].tid, NULL) != 0)
			return (-1);
		i++;
	}
	pthread_join(d->monitor, NULL);
	return (0);
}

static void	free_data(t_data *d)
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
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (parse_arguments(argc, argv) == FALSE)
		return (EXIT_FAILURE);
	if (init_data(argc, argv, &d) == FALSE)
		return (EXIT_FAILURE);
	if (create_threads(&d) == -1)
		return (EXIT_FAILURE);
	free_data(&d);
	return (EXIT_SUCCESS);
}
