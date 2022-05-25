/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 09:52:31 by abba          #+#    #+#                 */
/*   Updated: 2022/05/23 15:30:54 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_data *data)
{
	pthread_mutex_lock(&data->philo->mutex[data->l_fork]);
	pthread_mutex_lock(&data->philo->mutex[data->r_fork]);
	set_status(data, data->id, G_FORK);
	set_status(data, data->id, G_FORK);
}

void	philo_think(t_data *data)
{
	set_status(data, data->id, THINKING);
}

void	philo_eat(t_data *data)
{
	take_fork(data);
	set_status(data, data->id, EATING);
	usleep_ms(data->philo->time_eat);
	pthread_mutex_lock(&data->philo->eat);
	pthread_mutex_lock(&data->philo->l_print);
	data->l_eat = get_time();
	pthread_mutex_lock(&data->philo->over_locl);
	pthread_mutex_unlock(&data->philo->l_print);
	if (data->philo->extra)
		data->num_eat--;
	pthread_mutex_unlock(&data->philo->eat);
	pthread_mutex_unlock(&data->philo->over_locl);
	pthread_mutex_unlock(&data->philo->mutex[data->l_fork]);
	pthread_mutex_unlock(&data->philo->mutex[data->r_fork]);
}

void	philo_sleep(t_data *data)
{
	set_status(data, data->id, SLEEPING);
	usleep_ms(data->philo->time_sleap);
}

void	*routine(void *value)
{
	t_data	*data;

	data = (t_data *)value;
	if (data->id % 2 == 1)
		usleep(50);
	while (1)
	{
		pthread_mutex_lock(&data->philo->over_locl);
		if (data->philo->over)
		{
			pthread_mutex_unlock(&data->philo->over_locl);
			break ;
		}
		pthread_mutex_unlock(&data->philo->over_locl);
		if (data->philo->p_num == 1)
		{
			set_status(data, data->id, G_FORK);
			usleep_ms(data->philo->time_die);
			break ;
		}
		philo_eat(data);
		if (data->philo->extra && data->num_eat <= 0)
			break ;
		philo_sleep(data);
		philo_think(data);
	}
	return (0);
}
