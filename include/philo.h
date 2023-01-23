/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:24:48 by etomiyos          #+#    #+#             */
/*   Updated: 2023/01/23 20:47:10 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//gettimeofday(),
# include <sys/time.h>

# define MSG_INVALID_ARGS "philo: invalid number of arguments"
# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_philo
{
}	t_philo;

typedef struct s_data
{
	int		number_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		times_each_philo_must_eat;
	t_philo	**philos;
}	t_data;

size_t	ft_strlen(const char *str);
void	ft_putendl_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);

int		check_arguments(int argc);
int		parse_arguments(int argc, char **argv, t_data **d);

#endif