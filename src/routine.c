/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:39:06 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/03 10:11:27 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	philo->meal++;
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

void	*monitor(void *d)
{
	// int			i;
	t_data		*data;

	data = ((t_data *)d);
	(void)data;
	// while (1)
	// {
	// 	i = 0;
	// 	while (i < data->number_of_philos)
	// 	{
	// 		if (data->philos[i].meal == data->times_each_philo_must_eat)
	// 		{
	// 			// printf("there you are\n");
	// 		}
	// 		i++;
	// 	}
	// 	// while (i < data->number_of_philos)
	// 	// {
	// 	// 	if (timestamp() - data->philos[i].last_meal > data->philos->d->time_to_die)
	// 	// 	{
	// 	// 		printf("|%ld|\n", timestamp() - data->philos[i].last_meal);
	// 	// 		// return ;
	// 	// 	}
	// 	// 	i++;
	// 	// }
	// 	usleep(5000);
	// }
	return (NULL);
}

void	print_msg(t_philo *philo, int id_msg)
{
	t_ms	last_done;

	pthread_mutex_lock(&philo->d->print_lock);
	pthread_mutex_lock(&philo->d->lock_meal);
	last_done = timestamp();
	if (id_msg == 0)
	{
		philo->last_meal = last_done;
		printf("\001\e[32m%ld %d %s\e[00m\002\n", last_done - philo->d->start, philo->id, MSG_EAT);
	}
	if (id_msg == 1)
		printf("\001\e[32m%ld %d %s\e[00m\002\n", last_done - philo->d->start, philo->id, MSG_FORK);
	if (id_msg == 2)
		printf("\001\e[32m%ld %d %s\e[00m\002\n", last_done - philo->d->start, philo->id, MSG_SLEEP);
	if (id_msg == 3)
		printf("\001\e[32m%ld %d %s\e[00m\002\n", last_done - philo->d->start, philo->id, MSG_THINK);
	pthread_mutex_unlock(&philo->d->print_lock);
	pthread_mutex_unlock(&philo->d->lock_meal);
}

void	*routine(void *d)
{
	t_philo		*philo;

	philo = ((t_philo *)d);
	while (1)
	{
		if (philo->id == philo->d->number_of_philos) //mudar para % 2 == 0
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
		if (philo->meal == philo->d->times_each_philo_must_eat)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
