/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:25:18 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/06 17:55:18 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arguments(int argc, char **argv, t_data *d)
{
	int	num_philos;
	int	i;

	if (argc < 5 || argc > 6)
		return (ft_putendl_fd(MSG_INVALID_ARGS, STDERR), -1);
	i = 1;
	while (argv[i])
	{
		if (valid_number(argv[i]) == -1)
			return (ft_putendl_fd(MSG_INVALID_ARGS, STDERR), -1);
		i++;
	}
	num_philos = ft_atoi(argv[1]);
	if (num_philos > MAX_PHILOS || num_philos == 0)
		return (ft_putendl_fd(MSG_INVALID_ARGS, STDERR), -1);
	init_data(argc, argv, d);
	return (0);
}

int	create_threads(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_philos)
	{
		if (pthread_create(&d->philos[i].tid, NULL, routine,
				(void *)&d->philos[i]) != 0)
			return (-1);
		i++;
	}
	pthread_create(&d->monitor, NULL, monitor, (void *)d);
	i = 0;
	while (i < d->num_philos)
	{
		if (pthread_join(d->philos[i].tid, NULL) != 0)
			return (-1);
		i++;
	}
	pthread_join(d->monitor, NULL);
	return (0);
}

void	free_data(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_philos)
	{
		pthread_mutex_destroy(&d->forks[i]);
		pthread_mutex_destroy(&d->philos[i++].meal_lock);
	}
	pthread_mutex_destroy(&d->print.lock);
	pthread_mutex_destroy(&d->satisfied.lock);
	pthread_mutex_destroy(&d->dinner_is_over.lock);
	free(d->forks);
	free(d->philos);
	free(d);
}

int	main(int argc, char **argv)
{
	t_data	*d;

	d = ft_calloc(1, sizeof(t_data));
	if (parse_arguments(argc, argv, d) == -1)
	{
		free(d);
		return (EXIT_FAILURE);
	}
	if (create_threads(d) == -1)
	{
		free(d);
		return (EXIT_FAILURE);
	}
	free_data(d);
	return (EXIT_SUCCESS);
}
