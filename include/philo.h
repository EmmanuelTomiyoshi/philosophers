/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:24:48 by etomiyos          #+#    #+#             */
/*   Updated: 2023/01/27 12:26:14 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>

# define MSG_INVALID_ARGS "philo: invalid arguments"
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define MAX_INT 2147483647

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			eat;
	int			sleep;
	int			think;
	pthread_t	tid;
	t_data		*d;
}	t_philo;

typedef struct s_data
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_philo_must_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_data;

size_t	ft_strlen(const char *str);
void	ft_putendl_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nelem, size_t elsize);

int		check_arguments(int argc);
int		parse_arguments(int argc, char **argv, t_data *d);
void	free_data(t_data *d);

#endif