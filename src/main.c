/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:25:18 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/06 15:24:38 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

// index		left	right
// 1 		=	2		8
// 2 		=	3		1
// 3 		=	4		2
// 4 		=	5		3
// 5 		=	6		4
// 6 		=	7		5
// 7 		=	8		6
// 8 		=	1		7

//garfos, mensagens na tela e fim da simulação

//NUM_PHILO		POR_VEZ
//1				0
//2				1			N / 2
//3				1			N / 2
//4				2
//5				2
//6				3
//7				3
//8				4
//9				4
