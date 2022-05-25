/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   status.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 10:13:22 by abba          #+#    #+#                 */
/*   Updated: 2022/03/22 09:39:13 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
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

	sem_wait(data->philo->l_print);
	if (data->philo->over)
	{
		sem_post(data->philo->l_print);
		return ;
	}
	printf("%s %zu %d %s" RESET, color[value], date, id, printl[value]);
	sem_post(data->philo->l_print);
}

void	set_status(t_data *data, int id, int value)
{
	size_t	date;

	date = get_time() - data->philo->time;
	sem_wait(data->philo->over_lock);
	if (!data->philo->over)
	{
		sem_post(data->philo->over_lock);
		print_routine(date, data, id, value);
		return ;
	}
	sem_post(data->philo->over_lock);
}
