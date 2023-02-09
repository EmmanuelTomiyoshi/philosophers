/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:50:19 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/09 14:40:36 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_safe_content(t_safe *s)
{
	int	content;

	pthread_mutex_lock(&s->lock);
	content = s->content;
	pthread_mutex_unlock(&s->lock);
	return (content);
}

int	add_safe_content(t_safe *s)
{
	int	content;

	pthread_mutex_lock(&s->lock);
	s->content++;
	content = s->content;
	pthread_mutex_unlock(&s->lock);
	return (content);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (timestamp() - philo->last_meal > philo->d->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		print_msg(philo, DIED);
		add_safe_content(&philo->d->dinner_is_over);
		return (1);
	}
	else
		pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

void	hold_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
}

t_ms	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
