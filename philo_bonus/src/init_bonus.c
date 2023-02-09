/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:01:26 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/08 22:24:19 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <fcntl.h>
#include <semaphore.h>

static void	init_philos(t_data *d)
{
	int	i;

	d->philos = ft_calloc(d->num_philos, sizeof(t_philo));
	d->forks = ft_calloc(d->num_philos, sizeof(pthread_mutex_t));
	i = 0;
	// d->sforks = sem_open("/forks", O_CREAT, 06444, d->num_philos);
	while (i < d->num_philos)
		pthread_mutex_init(&d->forks[i++], NULL);
	i = 0;
	while (i < d->num_philos)
	{
		d->philos[i].d = d;
		d->philos[i].id = i + 1;
		d->philos[i].left_fork = &d->forks[i];
		d->philos[i].right_fork = &d->forks[(i + 1) % d->num_philos];
		d->philos[i].last_meal = d->start;
		d->philos[i].meal = 0;
		pthread_mutex_init(&d->philos[i].meal_lock, NULL);
		i++;
	}
}

sem_t	*create_semaphore(const char *name, unsigned int value)
{
	sem_t	*sem;
	int		mode;

	sem_unlink(name);
	mode = S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR;
	sem = sem_open(name, O_CREAT, mode, value);
	if (sem == SEM_FAILED)
	{
		printf("philo: failed to create a semaphore\n");
		exit(EXIT_FAILURE);
	}
	return (sem);
}

void	init_data(int argc, char **argv, t_data *d)
{
	memset(d, 0, sizeof(t_data));
	// sem_unlink("/lock_print");
	// sem_unlink("forks");
	d->forks = NULL;
	d->philos = NULL;
	d->print.content = 0;
	d->satisfied.content = 0;
	d->dinner_is_over.content = 0;
	d->start = timestamp();
	d->num_philos = ft_atoi(argv[1]);
	d->time_to_die = ft_atoi(argv[2]);
	d->time_to_eat = ft_atoi(argv[3]);
	d->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		d->times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		d->times_each_philo_must_eat = 0;
	
	pthread_mutex_init(&d->print.lock, NULL);
	pthread_mutex_init(&d->satisfied.lock, NULL);
	pthread_mutex_init(&d->dinner_is_over.lock, NULL);
	init_philos(d);
}
