/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:39:06 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/03 13:16:15 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

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

int	get_safe_content(t_safe s)
{
	int	content;

	pthread_mutex_lock(&s.lock);
	content = s.content;	
	pthread_mutex_unlock(&s.lock);
	return (content);
}

int	add_safe_content(t_safe s)
{
	int	content;

	pthread_mutex_lock(&s.lock);
	content = ++s.content;
	pthread_mutex_unlock(&s.lock);
	return (content);
}

void	*monitor(void *d)
{
	t_data	*data;

	data = ((t_data *)d);
	while (1)
	{
		if (get_safe_content(data->dinner_is_over) == data->number_of_philos)
			break ;
		usleep(10000);
	}
	return (NULL);
}

void	print_msg(t_philo *philo, int id_msg)
{
	t_ms	last_done;

	pthread_mutex_lock(&philo->d->print.lock);
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
	pthread_mutex_unlock(&philo->d->print.lock);
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
		if (get_safe_content(philo->d->dinner_is_over))
			return (NULL);
		eating(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (philo->meal == philo->d->times_each_philo_must_eat)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	if (add_safe_content(philo->d->satisfied) == philo->d->number_of_philos)
		add_safe_content(philo->d->dinner_is_over);
	return (NULL);
}



