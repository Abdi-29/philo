/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 09:52:31 by abba          #+#    #+#                 */
/*   Updated: 2022/03/23 12:59:56 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "colours.h"

static void	take_fork(t_data *data)
{
	sem_wait(data->philo->semaphore);
	sem_wait(data->philo->semaphore);
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
	sem_wait(data->philo->eat);
	sem_wait(data->philo->l_print);
	sem_wait(data->philo->l_clock);
	data->l_eat = get_time();
	sem_wait(data->philo->over_lock);
	sem_post(data->philo->l_print);
	sem_post(data->philo->l_clock);
	if (data->philo->extra)
		data->num_eat--;
	sem_post(data->philo->eat);
	sem_post(data->philo->over_lock);
	sem_post(data->philo->semaphore);
	sem_post(data->philo->semaphore);
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
	while (1)
	{
		sem_wait(data->philo->over_lock);
		if (data->philo->over)
		{
			sem_post(data->philo->over_lock);
			break ;
		}
		sem_post(data->philo->over_lock);
		if (data->philo->p_num == 1)
		{
			set_status(data, data->id, G_FORK);
			usleep_ms(data->philo->time_die);
			break ;
		}
		philo_eat(data);
		if (data->philo->extra && data->philo->t_eat == data->philo->all_eat)
			break ;
		philo_sleep(data);
		philo_think(data);
	}
	return (0);
}
