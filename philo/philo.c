/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 19:55:32 by abba          #+#    #+#                 */
/*   Updated: 2022/03/19 17:39:20 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

int	testing(t_philo *data, int argc)
{
	create_thread(data);
	(void)argc;
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	data;

	if (argc < 5 || argc > 6)
	{
		printf(RED "invalid input\n" RESET);
		return (1);
	}
	if (!parsing(&data, argv, argc))
		return (1);
	if (!testing(&data, argc))
		return (1);
	return (0);
}
