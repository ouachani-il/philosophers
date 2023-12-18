/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilham_oua <ilham_oua@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:39:28 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/18 19:16:23 by ilham_oua        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	pthread_mutex_inti(&data->death, NULL);
	pthread_mutex_inti(&data->print, NULL);
	pthread_mutex_inti(&data->lock, NULL);
	data->forks = mutex;
}


void	init_philos(t_data *data)
{
	t_philo	*philo;
	int		i;
	
	philo = malloc(sizeof(t_philo) * data->nb_philos);
	if (!philo)
		return (printf("fail in philo structure allocation\n"));
	memset(philo, 0, data->nb_philos);
	i = 0;
	while (i < data->nb_philos)
	{
		philo[i].id = i;
		philo[i].time_to_die = data->time_to_die;
		philo[i].time_to_eat = data->time_to_eat;
		philo[i].time_to_sleep = data->time_to_sleep;
		philo[i].nb_meals = 0;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % data->nb_philos;
		philo[i].nb_philos = data->nb_philos;
		philo[i].data = data;
		philo[i].time_last_meal = current_time();
		philo[i].is_dead = 0;
		i++;
	}
	data->philo = philo;
}

void	init_data(t_data *data, int ac, char **av)
{
	data->nb_philos = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	data->is_dead = 0;
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = -1;
	data->is_full = data->nb_meals * data->nb_philos;
	data->belly = 0;
	data->dead = false;
	data->full = false;
}