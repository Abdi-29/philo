/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   status.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 10:13:22 by abba          #+#    #+#                 */
/*   Updated: 2022/03/21 10:13:34 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

static void	print_routine(size_t date, t_data *data, int id, int value)
{
	const char	*printl[] = {
		"is eating\n",
		"is sleeping\n",
		"is thinking\n",
		"has taken a fork\n"
	};
	const char	*color[] = {
		"\x1B[32m",
		"\x1B[33m",
		"\x1B[34m",
		"\x1B[36m"
	};

	pthread_mutex_lock(&data->philo->l_print);
	if (data->philo->over)
	{
		pthread_mutex_unlock(&data->philo->l_print);
		return ;
	}
	printf("%s %zu %d %s" RESET, color[value], date, id, printl[value]);
	pthread_mutex_unlock(&data->philo->l_print);
}

void	set_status(t_data *data, int id, int value)
{
	size_t	date;

	date = get_time() - data->philo->time;
	pthread_mutex_lock(&data->philo->over_locl);
	if (!data->philo->over)
	{
		pthread_mutex_unlock(&data->philo->over_locl);
		print_routine(date, data, id, value);
		return ;
	}
	pthread_mutex_unlock(&data->philo->over_locl);
}
