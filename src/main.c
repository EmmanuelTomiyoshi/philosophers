/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:25:18 by etomiyos          #+#    #+#             */
/*   Updated: 2023/01/27 12:26:50 by etomiyos         ###   ########.fr       */
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
	t_philo	*philo;

	philo = ((t_philo *)d);
	(void)philo;
	return (NULL);
}
// pthread_mutex_lock(&data->mutex);
// eating(d);
// pthread_mutex_unlock(&data->mutex);

//funções de pegar e soltar os garfos.
//implementar os ms usando gettimeofday.

int	create_threads(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->number_of_philos)
	{
		if (pthread_create(&d->philos[i].tid, NULL, routine,
				(void *)&d->philos[i]) != 0)
			return (-1);
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < d->number_of_philos)
	{
		if (pthread_join(d->philos[i].tid, NULL) != 0)
			return (-1);
		printf("Thread %d has finished\n", i);
		i++;
	}
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
	free_data(data);
	return (EXIT_SUCCESS);
}

//1 2 3 4 5 6 7 8

// index		left	right
// 1 		=	2		8
// 2 		=	3		1
// 3 		=	4		2
// 4 		=	5		3
// 5 		=	6		4
// 6 		=	7		5
// 7 		=	8		6
// 8 		=	1		7

//garfos, mensagens na tela e fim da simulação

//