/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:39:28 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/22 21:00:38 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("full");
	sem_unlink("death");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, S_IRWXU, data->nb_philos);
	data->print = sem_open("print", O_CREAT | O_EXCL, S_IRWXU, 1);
	data->full = sem_open("full", O_CREAT | O_EXCL, S_IRWXU, 0);
	data->death = sem_open("death", O_CREAT | O_EXCL, S_IRWXU, 0);	
}

void	init_philo(t_data *data)
{
	data->philo.time_die = data->time_die;
	data->philo.time_to_eat = data->time_to_eat;
	data->philo.time_to_sleep = data->time_to_sleep;
	data->philo.nb_meals = 0;
	data->philo.nb_philos = data->nb_philos;
	data->philo.data = data;
	data->philo.time_last_meal = current_time();
}

void	init_data(t_data *data, int ac, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->nb_philos = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->start = current_time();
	data->philo_id = malloc(sizeof(pid_t) * data->nb_philos);
	memset(data->philo_id, 0, sizeof(pid_t) * data->nb_philos);
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = -1;
}
