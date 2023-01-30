/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:25:18 by etomiyos          #+#    #+#             */
/*   Updated: 2023/01/30 14:19:02 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//memset, printf, malloc, free, write,
//usleep, gettimeofday

//pthread_detach
//pthread_mutex_destroy,

//pthread_join
//pthread_create

//pthread_mutex_init
//pthread_mutex_lock,
//pthread_mutex_unlock

void	eating(t_philo *philo)
{
	philo->eat = 25;
}

// void	gettimestamp(void)
// {
// 	struct timeval tv;
	
// 	gettimeofday(&tv, NULL);
// 	printf("Segundos: %ld\n", (long int)tv.tv_sec);
// 	printf("Microsegundos: %ld\n", (long int)tv.tv_usec);
// }

float	time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) * 1e-6 + end->tv_usec - start->tv_usec);
}

void	*routine(void *d)
{
	t_philo		*philo;

	philo = ((t_philo *)d);
	int j = 0;
	while (1)
	{
		dprintf(2, "%d | num: %d\n", philo->id, philo->d->number_of_philos);
		if (philo->id == philo->d->number_of_philos)
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		eating(philo);
		sleep(1);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (j == 1)
			break ;
		j++;
	}
	return (NULL);
}
// pthread_mutex_lock(&data->mutex);
// eating(d);
// pthread_mutex_unlock(&data->mutex);

//Funções de pegar e soltar os garfos.		FEITO
//Implementar os ms usando gettimeofday.
//Monitor: atualizar a var. que diz se alguém morreu + implementar 3 rotinas. Verificar a var.
//pra ver se morreu
//Log (mensagens) gerenciado por mutexes
//implementar 5 argumento (comer pelo menos X vez - must_eat)

int	create_threads(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->number_of_philos)
	{
		gettimeofday(&d->start, NULL);
		if (pthread_create(&d->philos[i].tid, NULL, routine,
				(void *)&d->philos[i]) != 0)
			return (-1);
		// printf("Thread %d has started\n", i);
		gettimeofday(&d->end, NULL);
		dprintf(2, "time spent: %0.f sec\n", time_diff(&d->start, &d->end));
		i++;
	}
	i = 0;
	while (i < d->number_of_philos)
	{
		if (pthread_join(d->philos[i].tid, NULL) != 0)
			return (-1);
		// printf("Thread %d has finished\n", i);
		// printf("fork[%d]: %d\n", i, d->philos[i].eat);
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