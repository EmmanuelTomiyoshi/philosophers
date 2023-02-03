/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:38:06 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/03 13:09:35 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *d)
{
	int	i;

	d->philos = ft_calloc(d->number_of_philos, sizeof(t_philo));
	d->forks = ft_calloc(d->number_of_philos, sizeof(pthread_mutex_t));
	i = 0;
	while (i < d->number_of_philos)
		pthread_mutex_init(&d->forks[i++], NULL);
	i = 0;
	while (i < d->number_of_philos)
	{
		d->philos[i].d = d;
		d->philos[i].id = i + 1;
		d->philos[i].left_fork = &d->forks[i];
		d->philos[i].right_fork = &d->forks[(i + 1) % d->number_of_philos];
		d->philos[i].last_meal = d->start;
		d->philos[i].meal = 0;
		i++;
	}
}

static void	init_data(int argc, char **argv, t_data *d)
{
	d->dinner_is_over.content = 0;
	d->print.content = 0;
	d->satisfied.content = 0;
	d->number_of_philos = ft_atoi(argv[1]);
	d->time_to_die = ft_atoi(argv[2]);
	d->time_to_eat = ft_atoi(argv[3]);
	d->time_to_sleep = ft_atoi(argv[4]);
	d->start = timestamp();
	if (argc == 6)
		d->times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		d->times_each_philo_must_eat = 0;
	pthread_mutex_init(&d->print.lock, NULL);
	pthread_mutex_init(&d->satisfied.lock, NULL);
	pthread_mutex_init(&d->dinner_is_over.lock, NULL);
	init_philos(d);
}

static int	valid_number(char *s)
{
	int		i;

	i = 0;
	if (s[0] == '+' && ft_strlen(s) > 1)
		s++;
	while (s && *s == '0')
		s++;
	if (*s == '\0')
		return (-1);
	if (ft_strlen(s) > 9)
		return (-1);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	parse_arguments(int argc, char **argv, t_data *d)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (valid_number(argv[i]) == -1)
			return (ft_putendl_fd(MSG_INVALID_ARGS, STDERR), -1);
		i++;
	}
	init_data(argc, argv, d);
	if (d->number_of_philos > 200 || d->number_of_philos == 0)
		return (ft_putendl_fd(MSG_INVALID_ARGS, STDERR), -1);
	return (0);
}

int	check_arguments(int argc)
{
	if (argc < 5 || argc > 6)
		return (ft_putendl_fd(MSG_INVALID_ARGS, STDERR), -1);
	return (0);
}
