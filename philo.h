/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:00:11 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/15 23:15:47 by ilouacha         ###   ########.fr       */
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

struct s_data;


typedef struct s_philo
{
	unsigned long	nb_meals;
	long long		start;
	long long		time_last_meal;
	int				id;
	int				is_dead;
	int				nb_philos;
	int				left_fork;
	int				right_fork;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	struct s_data	*data;
}		t_philo;

typedef struct s_data
{
	unsigned long	nb_philos;
	long long		start;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				belly;
	bool			full;
	bool			dead;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_t		*tid;
	pthread_t		thread_death;
	t_philo			*philo;
}		t_data;

void	print_action(char *str, t_data *data, int id);
long long	current_time();



#endif