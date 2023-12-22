/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:00:11 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/22 21:01:46 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <errno.h>

struct	s_data;

typedef struct s_philo
{
	long			time_last_meal;
	int				nb_meals;
	int				start_time;
	int				id;
	int				nb_philos;
	int				time_to_eat;
	int				time_die;
	int				time_to_sleep;
	struct s_data	*data;
}		t_philo;

typedef struct s_data
{
	int				nb_meals;
	long int		start;
	int				time_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_philos;
	pid_t			*philo_id;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*death;
	sem_t			*full;
	pthread_t		supervisor;
	pthread_t		death_thread;
	t_philo			philo;
}		t_data;

void		print_action(char *str, t_data *data, int id);
long long	current_time(void);
int			ft_parse(int ac, char **av);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		init_data(t_data *data, int ac, char **av);
void		init_semaphores(t_data *data);
void		init_philo(t_data *data);
void		ft_usleep(int time);
void		sleep_think(t_data *data);
void		eating(t_data *data);
void		routine_func(t_data *data);
void		start_routine(t_data *data);
void		*death(void *args);
int			ft_atoi(const char *nptr);
void		kill_process(t_data *data);

#endif