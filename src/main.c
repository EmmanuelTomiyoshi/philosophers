/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:25:18 by etomiyos          #+#    #+#             */
/*   Updated: 2023/01/25 12:35:36 by etomiyos         ###   ########.fr       */
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

void	*routine(void *d)
{
	int		i;
	t_data	*data;

	i = 0;
	data = ((t_data *)d);
	while (i < 1000)
	{
		pthread_mutex_lock(&data->mutex);
		data->meatballs++;
		pthread_mutex_unlock(&data->mutex);
		i++;
	}
	return (NULL);
}

int	create_threads(t_data **d)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(*d)->mutex, NULL);
	(*d)->th = ft_calloc((*d)->number_of_philos, sizeof(pthread_t));
	while (i < (*d)->number_of_philos)
	{
		if (pthread_create(&(*d)->th[i], NULL, routine, (void *)(*d)) != 0)
			return (-1);
		if (pthread_join((*d)->th[i], NULL) != 0)
			return (-1);
		i++;
	}
	pthread_mutex_destroy(&(*d)->mutex);
	printf("total is: %d\n", (*d)->meatballs);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (check_arguments(argc) == -1)
		return (EXIT_FAILURE);
	if (parse_arguments(argc, argv, &data) == -1)
		return (EXIT_FAILURE);
	if (create_threads(&data) == -1)
		return (EXIT_FAILURE);
	free_data(&data);
	return (EXIT_SUCCESS);
}
