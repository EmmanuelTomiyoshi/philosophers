/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:13:30 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/09 14:36:52 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	init_philos(t_data *d);
static t_bool	alloc_memory(t_data *d);
static void		*ft_calloc(size_t nelem, size_t elsize);

t_bool	init_data(int argc, char **argv, t_data *d)
{
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
	if (init_philos(d) == FALSE)
		return (FALSE);
	return (TRUE);
}

static t_bool	init_philos(t_data *d)
{
	int	i;

	if (alloc_memory(d) == FALSE)
		return (FALSE);
	i = 0;
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
	return (TRUE);
}

static t_bool	alloc_memory(t_data *d)
{
	d->philos = ft_calloc(d->num_philos, sizeof(t_philo));
	d->forks = ft_calloc(d->num_philos, sizeof(pthread_mutex_t));
	if (d->philos == NULL)
	{
		print_error(MSG_ERROR_ALLOC, NO_USAGE);
		return (FALSE);
	}
	if (d->forks == NULL)
	{
		print_error(MSG_ERROR_ALLOC, NO_USAGE);
		free(d->philos);
		return (FALSE);
	}
	return (TRUE);
}

static void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ptr;

	ptr = malloc(nelem * elsize);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, '\0', (nelem * elsize));
	return (ptr);
}
