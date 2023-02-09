/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:39:03 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/09 14:40:49 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_error(char *msg, t_bool usage)
{
	if (!msg)
		return ;
	printf("%s\n", msg);
	if (usage == TRUE)
	{
		printf("usage: %s %s %s %s [%s]\n",
			"number_of_philosophers",
			"time_to_die",
			"time_to_eat",
			"time_to_sleep",
			"number_of_times_each_philosopher_must_eat");
	}
}
