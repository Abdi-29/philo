/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 13:59:33 by abba          #+#    #+#                 */
/*   Updated: 2022/03/21 09:55:25 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_ms(size_t ms)
{
	size_t	current_time;

	current_time = get_time();
	while (get_time() - current_time < ms)
		usleep(150);
}

size_t	get_time(void)
{
	size_t			time;
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL))
		return (0);
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}
