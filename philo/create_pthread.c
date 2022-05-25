/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_pthread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 13:57:10 by abba          #+#    #+#                 */
/*   Updated: 2022/03/23 12:57:16 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "colours.h"

static int	init_philo(t_philo *philo)
{
	philo->mutex = malloc(philo->p_num * sizeof(pthread_mutex_t));
	if (!philo->mutex)
		return (0);
	philo->data = malloc(sizeof(t_data) * philo->p_num);
	if (!philo->data)
	{
		free(philo->mutex);
		return (0);
	}
	return (1);
}

static int	init_pthread_create(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->p_num)
	{
		if (pthread_create(&philo->data[i].th, NULL, &routine, &philo->data[i]))
		{
			printf(RED "failed to create thread\n" RESET);
			return (0);
		}
		if (pthread_create(&philo->data[i].check, NULL, \
			&death_check, &philo->data[i]))
		{
			printf(RED "failed to create thread\n" RESET);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	join_pthread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->p_num)
	{
		if (pthread_join(philo->data[i].th, NULL))
		{
			printf(RED "failed to create thread\n" RESET);
			return (0);
		}
		if (pthread_join(philo->data[i].check, NULL))
		{
			printf(RED "failed to create thread\n" RESET);
			return (0);
		}
		i++;
	}
	return (1);
}

void	create_thread(t_philo *philo)
{
	if (!init_philo(philo))
		return ;
	if (!init_data(philo))
		return ;
	philo->time = get_time();
	if (!init_pthread_create(philo))
		return ;
	if (!join_pthread(philo))
		return ;
	if (!destroy_phread(philo))
		return ;
	free(philo->mutex);
	free(philo->data);
}
