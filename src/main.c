/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:25:18 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/01 17:55:20 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/select.h>
#include <time.h>

//memset, printf, malloc, free, write,
//usleep, gettimeofday

//pthread_detach
//pthread_mutex_destroy,

//pthread_join
//pthread_create

//pthread_mutex_init
//pthread_mutex_lock,
//pthread_mutex_unlock

//milliseconds to microseconds
void	eating(t_philo *philo)
{
	usleep(philo->d->time_to_eat * 1000);
}

void	sleeping(t_philo *philo)
{
	usleep(philo->d->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	(void)philo;
}

void	print_msg(t_philo *philo, int id_msg)
{
	t_ms	last_done;

	pthread_mutex_lock(&philo->d->print_lock);
	last_done = timestamp() - philo->d->start;
	if (id_msg == 0)
	{
		// printf("ld: %ld lm: %ld resultado: %ld\n", last_done, philo->last_meal, last_done - philo->last_meal);
		if (last_done - philo->last_meal > philo->d->time_to_die)
		{
			// printf("%ld is bigger than %d\n", last_done - philo->last_meal, philo->d->time_to_die);
			// return ;
		}	
		philo->last_meal = last_done;
		printf("\001\e[32m%ld %d %s\e[00m\002\n", philo->last_meal, philo->id, MSG_EAT);
	}
	if (id_msg == 1)
		printf("\001\e[32m%ld %d %s\e[00m\002\n", last_done, philo->id, MSG_FORK);
	if (id_msg == 2)
		printf("\001\e[32m%ld %d %s\e[00m\002\n", last_done, philo->id, MSG_SLEEP);
	if (id_msg == 3)
		printf("\001\e[32m%ld %d %s\e[00m\002\n", last_done, philo->id, MSG_THINK);
	pthread_mutex_unlock(&philo->d->print_lock);
}

t_ms	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*routine(void *d)
{
	t_philo		*philo;

	philo = ((t_philo *)d);
	while (1)
	{
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
		print_msg(philo, 0);
		eating(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		sleeping(philo);
		thinking(philo);
		// sleep(3);
	}
	return (NULL);
}

//5			500		200 	200
//num_philo morre 	come 	dorme

//0ms ->

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