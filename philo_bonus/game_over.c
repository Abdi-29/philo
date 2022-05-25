/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_over.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 09:43:20 by abba          #+#    #+#                 */
/*   Updated: 2022/03/23 13:13:52 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "colours.h"

int	num_eat(t_data *data)
{
	if (data->num_eat != 0)
		return (1);
	return (0);
}

static void	lock(t_data *data)
{
	sem_wait(data->philo->eat);
	sem_wait(data->philo->l_print);
	sem_wait(data->philo->over_lock);
}

static void	unlock(t_data *data)
{
	sem_post(data->philo->eat);
	sem_post(data->philo->l_print);
	sem_post(data->philo->over_lock);
}

void	kill_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo->p_num)
	{
		kill(data->philo->process[i], SIGINT);
		i++;
	}
}

void	*death_check(void *value)
{
	t_data	*data;

	data = (t_data *)value;
	while (1)
	{
		lock(data);
		if (data->philo->extra && !num_eat(data))
			time_eat(data);
		if (get_time() - data->l_eat > data->philo->time_die \
			|| data->philo->over)
		{
			kill_process(data);
			if (data->philo->over)
				break ;
			printf(MAG "%zu %d died\n" RESET, \
				get_time() - data->philo->time, data->id);
			data->philo->over = true;
			break ;
		}
		unlock(data);
	}
	unlock(data);
	return (0);
}
