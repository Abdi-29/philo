/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 13:27:41 by abba          #+#    #+#                 */
/*   Updated: 2022/03/23 13:09:26 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

# define FORK  "fork_lock"
# define OVER  "game_over"
# define LOCK  "lock"
# define PRINT "l_print"
# define L_CLOCK "l_clock"

typedef enum s_option
{
	EATING,
	SLEEPING,
	THINKING,
	G_FORK
}				t_option;

typedef struct s_data
{
	int				philo_fork;
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
	int				check;
	int				t_eat;
	int				p_num;
	int				all_eat;
	size_t			time_die;
	bool			extra;
	int				time_eat;
	int				time_sleap;
	int				num_eat;
	bool			over;
	size_t			time;
	t_option		option;
	t_data			*data;
	sem_t			*semaphore;
	sem_t			*over_lock;
	size_t			clock;
	sem_t			*l_print;
	sem_t			*eat;
	sem_t			*l_clock;
	pid_t			*process;
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
void	time_eat(t_data *data);

#endif
