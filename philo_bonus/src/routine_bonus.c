/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:39:06 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/08 20:59:53 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eating(t_philo *philo)
{
	is_dead(philo);
	hold_forks(philo);
	print_msg(philo, FORK);
	print_msg(philo, FORK);
	print_msg(philo, EAT);
	philo->meal++;
	if (philo->meal == philo->d->times_each_philo_must_eat)
	{
		if (add_safe_content(&philo->d->satisfied) == philo->d->num_philos)
		{
			add_safe_content(&philo->d->dinner_is_over);
		}
	}
	if (get_safe_content(&philo->d->dinner_is_over) == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	usleep(philo->d->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (is_dead(philo) == 1)
		return (1);
	print_msg(philo, SLEEP);
	usleep(philo->d->time_to_sleep * 1000);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (is_dead(philo) == 1)
		return (1);
	print_msg(philo, THINK);
	return (0);
}

void	*routine(void *d)
{
	t_philo		*philo;

	philo = ((t_philo *)d);
	if (philo->d->num_philos == 1)
	{
		print_msg(philo, FORK);
		return (NULL);
	}
	while (1)
	{
		if (eating(philo) == 1)
			break ;
		if (sleeping(philo) == 1)
			break ;
		if (thinking(philo) == 1)
			break ;
	}
	return (NULL);
}

void	*monitor(void *d)
{
	int		i;
	t_data	*data;

	data = ((t_data *)d);
	while (get_safe_content(&data->dinner_is_over) == 0)
	{
		i = 0;
		while (i < data->num_philos)
		{
			is_dead(&data->philos[i]);
			i++;
		}
		usleep(5000);
	}
	return (NULL);
}
