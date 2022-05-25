/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 13:59:01 by abba          #+#    #+#                 */
/*   Updated: 2022/03/23 12:57:16 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_input(t_philo *philo, int argc)
{
	if (philo->p_num < 1)
		return (0);
	if (argc == 6 && philo->num_eat <= 0)
		return (0);
	return (1);
}

static int	parse(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parsing(t_philo *philo, char **argv, int argc)
{
	if (!parse(argv, argc))
		return (0);
	philo->p_num = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleap = ft_atoi(argv[4]);
	philo->extra = false;
	if (argc == 6)
	{
		philo->num_eat = ft_atoi(argv[5]);
		philo->extra = true;
	}
	if (!valid_input(philo, argc))
		return (0);
	return (1);
}
