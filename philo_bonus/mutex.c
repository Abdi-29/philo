/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/13 14:01:23 by abba          #+#    #+#                 */
/*   Updated: 2022/03/23 13:00:54 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "colours.h"

static int	init_semaphore(t_philo *philo)
{
	sem_unlink(FORK);
	philo->semaphore = sem_open(FORK, O_CREAT | O_EXCL, \
		0666, philo->p_num);
	if (philo->semaphore == SEM_FAILED)
		return (0);
	sem_unlink(LOCK);
	philo->eat = sem_open(LOCK, O_CREAT | O_EXCL, 0666, 1);
	if (philo->eat == SEM_FAILED)
		return (0);
	sem_unlink(OVER);
	philo->over_lock = sem_open(OVER, O_CREAT | O_EXCL, 0666, 1);
	if (philo->over_lock == SEM_FAILED)
		return (0);
	sem_unlink(PRINT);
	philo->l_print = sem_open(PRINT, O_CREAT | O_EXCL, 0666, 1);
	if (philo->l_print == SEM_FAILED)
		return (0);
	sem_unlink(L_CLOCK);
	philo->l_clock = sem_open(L_CLOCK, O_CREAT | O_EXCL, 0666, 1);
	if (philo->l_clock == SEM_FAILED)
		return (0);
	return (1);
}

int	init_data(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->p_num)
	{
		philo->data[i].l_eat = get_time();
		philo->data[i].id = i + 1;
		philo->data[i].philo = philo;
		if (philo->extra)
		{
			philo->data[i].num_eat = philo->num_eat;
			philo->check = philo->num_eat;
			philo->t_eat = 0;
			philo->all_eat = philo->check * philo->p_num;
		}
		i++;
	}
	philo->over = false;
	if (!init_semaphore(philo))
		return (0);
	philo->time = get_time();
	return (1);
}
