/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_over.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 09:43:20 by abba          #+#    #+#                 */
/*   Updated: 2022/04/22 16:38:37 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

int	num_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo->p_num)
	{
		if (data->philo->data[i].num_eat != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	mutex_lock(t_data *data)
{
	pthread_mutex_lock(&data->philo->eat);
	pthread_mutex_lock(&data->philo->l_print);
	pthread_mutex_lock(&data->philo->over_locl);
}

static void	mutex_unlock(t_data *data)
{
	pthread_mutex_unlock(&data->philo->over_locl);
	pthread_mutex_unlock(&data->philo->eat);
	pthread_mutex_unlock(&data->philo->l_print);
}

void	*death_check(void *value)
{
	t_data	*data;

	data = (t_data *)value;
	while (1)
	{
		mutex_lock(data);
		if (data->philo->extra && !num_eat(data))
		{
			data->philo->over = true;
			break ;
		}
		if (get_time() - data->l_eat > data->philo->time_die)
		{
			if (data->philo->over)
				break ;
			printf(MAG "%zu %d died\n" RESET, \
				get_time() - data->philo->time, data->id);
			data->philo->over = true;
			break ;
		}
		mutex_unlock(data);
		// usleep(1);
	}
	mutex_unlock(data);
	return (0);
}
