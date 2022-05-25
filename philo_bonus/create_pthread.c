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

#include "philo_bonus.h"
#include "colours.h"

static int	init_philo(t_philo *philo)
{
	philo->data = malloc(sizeof(t_data) * philo->p_num);
	if (!philo->data)
		return (0);
	philo->process = malloc(philo->p_num * sizeof(pid_t));
	if (!philo->process)
		return (0);
	return (1);
}

static int	init_pthread_create(t_data *data)
{
	if (pthread_create(&data->th, NULL, &routine, data) != 0)
	{
		printf(RED "failed to create thread\n" RESET);
		return (0);
	}
	if (pthread_create(&data->check, NULL, \
		&death_check, data) != 0)
	{
		printf(RED "failed to create thread\n" RESET);
		return (0);
	}
	pthread_join(data->th, NULL);
	pthread_join(data->check, NULL);
	return (1);
}

static int	philo_process(t_philo *philo)
{
	int		i;
	int		stat_loc;
	int		ret;

	i = 0;
	while (i < philo->p_num)
	{
		philo->process[i] = fork();
		if (philo->process[i] == 0)
			init_pthread_create(&philo->data[i]);
		i++;
	}
	while (1)
	{
		ret = waitpid(-1, &stat_loc, 0);
		if (ret == 0)
			break ;
	}
	return (1);
}

void	create_thread(t_philo *philo)
{
	if (!init_philo(philo))
		return ;
	if (!init_data(philo))
		return ;
	if (!philo_process(philo))
		return ;
	free(philo->data);
	free(philo->process);
}
