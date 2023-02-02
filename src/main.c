/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:25:18 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/02 19:39:46 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

//memset, printf, malloc, free, write,
//usleep, gettimeofday

//pthread_detach
//pthread_mutex_destroy,

//pthread_join
//pthread_create

//pthread_mutex_init
//pthread_mutex_lock,
//pthread_mutex_unlock

t_ms	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

//Funções de pegar e soltar os garfos.		FEITO
//Monitor: atualizar a var. que diz se alguém morreu + implementar 3 rotinas. Verificar a var pra ver se morreu
//Log (mensagens) gerenciado por mutexes
//implementar 5 argumento (comer pelo menos X vez - must_eat)

int	create_threads(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->number_of_philos)
	{
		if (pthread_create(&d->philos[i].tid, NULL, routine,
				(void *)&d->philos[i]) != 0)
			return (-1);
		// printf("Thread %d has started\n", i);
		i++;
	}
	pthread_create(&d->monitor, NULL, monitor, (void *)d);
	i = 0;
	while (i < d->number_of_philos)
	{
		if (pthread_join(d->philos[i].tid, NULL) != 0)
			return (-1);
		// printf("Thread %d has finished\n", i);
		// printf("fork[%d]: %d\n", i, d->philos[i].eat);
		i++;
	}
	pthread_join(d->monitor, NULL);
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

//NUM_PHILO		POR_VEZ
//1				0
//2				1			N / 2
//3				1			N / 2
//4				2
//5				2
//6				3
//7				3
//8				4
//9				4

// processo
// thread1----------------------------------------
// thread2----------------------------------------
// thread3----------------------------------------
// thread4----------------------------------------

//static t_bool is_dead = TRUE
//if (is_dead == TRUE)
//	encerrar;