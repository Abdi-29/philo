/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 14:01:23 by abba          #+#    #+#                 */
/*   Updated: 2022/03/23 12:57:16 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

static int	init_mutex(t_philo *philo)
{
	if (pthread_mutex_init(&philo->l_print, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philo->eat, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philo->over_locl, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philo->dead, NULL) != 0)
		return (0);
	return (1);
}

int	init_data(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->p_num)
	{
		if (pthread_mutex_init(&philo->mutex[i], NULL) != 0)
			return (0);
		philo->data[i].l_fork = i;
		philo->data[i].r_fork = (i + 1) % philo->p_num;
		philo->data[i].id = i + 1;
		philo->data[i].l_eat = get_time();
		philo->data[i].philo = philo;
		if (philo->extra)
			philo->data[i].num_eat = philo->num_eat;
		i++;
	}
	philo->over = false;
	if (!init_mutex(philo))
		return (0);
	return (1);
}

int	destroy_phread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->p_num)
	{
		if (pthread_mutex_destroy(&philo->mutex[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_destroy(&philo->l_print) != 0)
		return (0);
	if (pthread_mutex_destroy(&philo->eat) != 0)
		return (0);
	if (pthread_mutex_destroy(&philo->dead) != 0)
		return (0);
	if (pthread_mutex_destroy(&philo->over_locl) != 0)
		return (0);
	return (1);
}
