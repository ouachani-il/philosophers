/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:21:09 by ilham_oua         #+#    #+#             */
/*   Updated: 2023/12/22 20:55:05 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*supervisor(void *args)
{
	int		i;
	t_data	*data;

	data = (t_data *)args;
	i = 0;
	while (i < data->nb_philos)
	{
		sem_wait(data->full);
		i++;
	}
	sem_wait(data->print);
	printf("All philos have eaten!\n");
	sem_post(data->death);
	return (NULL);
}

void	routine_func(t_data *data)
{
	data->philo.time_last_meal = current_time();
	pthread_create(&data->death_thread, NULL, &death, data);
	pthread_detach(data->death_thread);
	if (data->philo.id % 2 == 0)
		ft_usleep(20);
	while (1)
	{
		eating(data);
		if (data->nb_philos == 1)
			return ;
		sleep_think(data);
	}
}

void	*death(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while (1)
	{
		if (current_time() - data->philo.time_last_meal > data->time_die)
		{
			sem_wait(data->print);
			print_action("died", data, data->philo.id);
			sem_post(data->death);
			break ;
		}
	}
	return (NULL);
}

void	start_routine(t_data *data)
{
	int	i;

	i = -1;
	pthread_create(&data->supervisor, NULL, &supervisor, data);
	pthread_detach(data->supervisor);
	while (++i < data->nb_philos)
	{
		data->philo.id = i;
		data->philo_id[i] = fork();
		if (data->philo_id[i] == -1)
		{
			printf("process failed\n");
			return ;
		}
		if (data->philo_id[i] == 0)
		{
			init_philo(data);
			routine_func(data);
		}
	}
	sem_wait(data->death);
	return ;
}
