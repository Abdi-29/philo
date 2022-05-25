/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_eat.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/23 13:07:43 by abba          #+#    #+#                 */
/*   Updated: 2022/03/23 13:09:19 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	time_eat(t_data *data)
{
	data->philo->t_eat++;
	if (data->philo->t_eat == data->philo->check * data->philo->p_num)
		data->philo->over = true;
}
