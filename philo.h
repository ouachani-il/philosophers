/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:00:11 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/22 16:09:20 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

struct	s_data;

typedef struct s_philo
{
	unsigned long	nb_meals;
	long long		start_time;
	long long		time_last_meal;
	int				id;
	int				is_dead;
	int				nb_philos;
	int				time_to_eat;
	int				time_die;
	int				time_to_sleep;
	struct s_data	*data;
}		t_philo;

typedef struct s_data
{
	unsigned long	nb_meals;
	long long		start;
	int				time_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_philos;
	int				belly;
	int				is_dead;
	int				all_full;
	bool			full;
	bool			dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_t		*tid;
	pthread_t		thread2;
	t_philo			*philo;
}		t_data;

void		print_action(char *str, t_data *data, int id);
long long	current_time(void);
int			ft_parse(int ac, char **av);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		init_data(t_data *data, int ac, char **av);
void		init_philos(t_data *data);
void		init_mutex(t_data *data);
void		ft_usleep(int time, t_data *data);
void		release_forks(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		eating_suite(t_philo *philo);
void		eating(t_philo *philo);
//void		*(void *args);
void		*routine_func(void *args);
void		start_routine(t_data *data);
void		end_routine(t_data *data);
void		*death_philo(void *args);
void		destroy_and_free(t_data *data);
int			ft_atoi(const char *nptr);

#endif