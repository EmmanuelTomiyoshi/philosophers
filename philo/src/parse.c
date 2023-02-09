/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:38:06 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/09 14:41:39 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			valid_number(char *s);
static int			ft_isdigit(int c);
static size_t		ft_strlen(const char *str);

int	parse_arguments(int argc, char **argv)
{
	int	num_philos;
	int	i;

	if (argc < 5 || argc > 6)
	{
		print_error(MSG_INVALID_NB_ARGS, USAGE);
		return (FALSE);
	}
	i = 0;
	while (argv[++i])
	{
		if (valid_number(argv[i]) == FALSE)
		{
			print_error(MSG_INVALID_ARGS, USAGE);
			return (FALSE);
		}
	}
	num_philos = ft_atoi(argv[1]);
	if (num_philos > MAX_PHILOS || num_philos == 0)
	{
		print_error(MSG_INVALID_PHILO_NB, USAGE);
		return (FALSE);
	}
	return (TRUE);
}

static int	valid_number(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+' && ft_strlen(s) > 1)
		s++;
	while (s && *s == '0')
		s++;
	if (*s == '\0')
		return (TRUE);
	if (ft_strlen(s) > 9)
		return (FALSE);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i])
	{
		if (!ft_isdigit(nptr[i]))
			return (sign * res);
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (sign * res);
}

static size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}
