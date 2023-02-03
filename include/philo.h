/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:24:48 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/03 13:06:47 by etomiyos         ###   ########.fr       */
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

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define MAX_INT 2147483647
# define MSG_EAT "is eating"
# define MSG_FORK "has taken a fork"
# define MSG_SLEEP "is sleep"
# define MSG_THINK "is thinking"
# define MSG_DIED "died"
# define MSG_INVALID_ARGS "philo: invalid arguments"

typedef struct s_data	t_data;
typedef long			t_ms;

typedef struct	s_safe
{
	int				content;
	pthread_mutex_t	lock;
}	t_safe;

typedef struct s_philo
{
	int				id;
	int				eat;
	int				sleep;
	int				think;
	int				meal;
	t_ms			last_meal;
	t_data			*d;
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_data
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_philo_must_eat;
	t_safe			dinner_is_over;		//
	t_safe			satisfied;			//
	t_safe			print;			//
	t_ms			start;
	t_philo			*philos;
	pthread_t		monitor;			//
	pthread_mutex_t	*forks;				//
}	t_data;

size_t	ft_strlen(const char *str);
void	ft_putendl_fd(char *s, int fd);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nelem, size_t elsize);

int		check_arguments(int argc);
int		parse_arguments(int argc, char **argv, t_data *d);
void	*routine(void *d);
void	print_msg(t_philo *philo, int id_msg);
t_ms	timestamp(void);
void	free_data(t_data *d);
void	*monitor(void *d);

#endif