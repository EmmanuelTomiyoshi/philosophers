/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:25:18 by etomiyos          #+#    #+#             */
/*   Updated: 2023/01/27 11:43:49 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//memset, printf, malloc, free, write,
//usleep, gettiimeofday

//pthread_detach
//pthread_mutex_destroy,

//pthread_join
//pthread_create

//pthread_mutex_init
//pthread_mutex_lock,
//pthread_mutex_unlock

void	eating(t_data *d)
{
	d->eat += 5;
}

void	*routine(void *d)
{
	t_data	*data;

	data = ((t_data *)d);
	
	pthread_mutex_lock(&data->mutex);
	eating(d);
	pthread_mutex_unlock(&data->mutex);
	return (NULL);
}

int	create_threads(t_data *d)
{
	int	i;

	i = 0;
	pthread_mutex_init(&d->mutex, NULL);
	d->th = ft_calloc(d->number_of_philos, sizeof(pthread_t));
	d->eat = 0;
	d->think = 0;
	d->sleep = 0;
	while (i < d->number_of_philos)
	{
		if (pthread_create(&d->th[i], NULL, routine, (void *)d) != 0)
			return (-1);
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < d->number_of_philos)
	{
		if (pthread_join(d->th[i], NULL) != 0)
			return (-1);
		printf("Thread %d has finished\n", i);
		i++;
	}
	printf("total\neat: %d\n", d->eat);
	printf("total\nthink: %d\n", d->think);
	printf("total\nsleep: %d\n", d->sleep);
	pthread_mutex_destroy(&d->mutex);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (check_arguments(argc) == -1)
		return (EXIT_FAILURE);
	if (parse_arguments(argc, argv, data) == -1)
		return (EXIT_FAILURE);
	if (create_threads(data) == -1)
		return (EXIT_FAILURE);
	free_data(&data);
	return (EXIT_SUCCESS);
}
