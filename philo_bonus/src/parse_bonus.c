/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etomiyos <etomiyos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:38:06 by etomiyos          #+#    #+#             */
/*   Updated: 2023/02/08 22:05:33 by etomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	valid_number(char *s)
{
	int		i;

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

t_bool	parse_arguments(int argc, char **argv)
{
	int	num_philos;
	int	i;

	if (argc < 5 || argc > 6)
	{
		print_error(MSG_INVALID_NB_ARGS);
		return (FALSE);
	}
	i = 0;
	while (argv[++i])
	{
		if (valid_number(argv[i]) == FALSE)
		{
			print_error(MSG_INVALID_ARGS);
			return (FALSE);
		}
	}
	num_philos = ft_atoi(argv[1]);
	if (num_philos > MAX_PHILOS || num_philos == 0)
	{
		print_error(MSG_INVALID_PHILO_NB);
		return (FALSE);
	}
	return (TRUE);
}
