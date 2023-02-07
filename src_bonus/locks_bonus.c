/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:50:19 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/07 11:57:15 by etomiyos         ###   ########.fr       */
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

void	print_msg(t_philo *philo, int id_msg)
{
	t_ms	last_done;

	last_done = timestamp();
	pthread_mutex_lock(&philo->d->print.lock);
	if (id_msg == EAT && !get_safe_content(&philo->d->dinner_is_over))
	{
		pthread_mutex_lock(&philo->meal_lock);
		philo->last_meal = timestamp();
		pthread_mutex_unlock(&philo->meal_lock);
		printf("%ld %d %s\n", last_done - philo->d->start, philo->id, MSG_EAT);
	}
	if (id_msg == FORK && !get_safe_content(&philo->d->dinner_is_over))
		printf("%ld %d %s\n", last_done - philo->d->start, philo->id, MSG_FORK);
	if (id_msg == SLEEP && !get_safe_content(&philo->d->dinner_is_over))
		printf("%ld %d %s\n", last_done - philo->d->start, philo->id, MSG_SLEEP);
	if (id_msg == THINK && !get_safe_content(&philo->d->dinner_is_over))
		printf("%ld %d %s\n", last_done - philo->d->start, philo->id, MSG_THINK);
	if (id_msg == DIED && !get_safe_content(&philo->d->dinner_is_over))
		printf("%ld %d %s\n", last_done - philo->d->start, philo->id, MSG_DIED);
	pthread_mutex_unlock(&philo->d->print.lock);
}
