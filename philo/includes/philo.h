/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/07 19:54:45 by abba          #+#    #+#                 */
/*   Updated: 2022/03/23 12:57:16 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>

typedef enum s_option
{
	EATING,
	SLEEPING,
	THINKING,
	G_FORK
}				t_option;

typedef struct s_data
{
	int				l_fork;
	int				r_fork;
	int				id;
	int				num_eat;
	t_option		option;
	size_t			l_eat;
	pthread_t		th;
	pthread_t		check;
	struct s_philo	*philo;
}			t_data;				

typedef struct s_philo
{
	int				p_num;
	size_t			time_die;
	bool			extra;
	int				time_eat;
	int				time_sleap;
	int				num_eat;
	bool			over;
	pthread_mutex_t	over_locl;
	size_t			time;
	pthread_mutex_t	*mutex;
	t_option		option;
	t_data			*data;
	size_t			clock;
	pthread_mutex_t	l_print;
	pthread_mutex_t	dead;
	pthread_mutex_t	eat;
}				t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	create_thread(t_philo *philo);
size_t	get_time(void);
int		parsing(t_philo *philo, char **argv, int argc);
int		init_data(t_philo *philo);
int		destroy_phread(t_philo *philo);
void	set_status(t_data *data, int id, int value);
void	*routine(void *value);
int		game_over(t_data *data);
void	*death_check(void *value);
void	usleep_ms(size_t ms);
void	unlock_forks(t_data *data);

#endif
