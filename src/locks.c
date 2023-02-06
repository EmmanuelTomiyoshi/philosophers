/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:50:19 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/06 14:03:28 by etomiyos         ###   ########.fr       */
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

void	*monitor(void *d)
{
	t_data	*data;

	data = ((t_data *)d);
	while (get_safe_content(&data->dinner_is_over) == 0)
	{
		usleep(2500);
	}
	return (NULL);
}

void	print_msg(t_philo *philo, int id_msg)
{
	t_ms	last_done;

	last_done = timestamp();
	pthread_mutex_lock(&philo->d->print.lock);
	if (id_msg == EAT)
	{
		if (philo->id == 1)
			printf("|%ld|\n", last_done - philo->last_meal);
		philo->last_meal = last_done;
		// printf("\001\e[32m%ld %d %s\e[00m\002\n", last_done - philo->d->start, philo->id, MSG_EAT);
	}
	// if (id_msg == FORK)
	// 	printf("\001\e[32m%ld %d %s\e[00m\002\n", last_done - philo->d->start, philo->id, MSG_FORK);
	// if (id_msg == SLEEP)
	// 	printf("\001\e[32m%ld %d %s\e[00m\002\n", last_done - philo->d->start, philo->id, MSG_SLEEP);
	// if (id_msg == THINK)
	// 	printf("\001\e[32m%ld %d %s\e[00m\002\n", last_done - philo->d->start, philo->id, MSG_THINK);
	pthread_mutex_unlock(&philo->d->print.lock);
}
