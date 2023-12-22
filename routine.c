/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:21:09 by ilham_oua         #+#    #+#             */
/*   Updated: 2023/12/22 16:07:16 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_func(void *args)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)args;
	data = philo->data;
	philo->start_time = current_time();
	philo->time_last_meal = current_time();
	if (philo->id % 2 == 0)
		ft_usleep(20, data);
	while (data->dead == false && data->full == false)
	{
		eating(philo);
		if (data->dead == false || data->full == false)
			sleeping(philo);
		if (data->dead == false || data->full == false)
			thinking(philo);
	}
	return (NULL);
}

void	*death_philo(void *args)
{
	int		i;
	t_data	*data;

	data = (t_data *)args;
	i = 0;
	while (1)
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			if (current_time() - data->philo[i].time_last_meal > data->time_die
				&& data->full == false)
			{
				pthread_mutex_lock(&data->print);
				if (data->nb_philos == 1)
					pthread_mutex_unlock(&data->forks[data->philo[i].id]);
				print_action("died", data, i);
				data->dead = true;
				pthread_mutex_unlock(&data->print);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	start_routine(t_data *data)
{
	pthread_t	*thread_id;
	int			i;

	i = 0;
	thread_id = malloc(sizeof(pthread_t) * data->nb_philos);
	data->start = current_time();
	pthread_create(&data->thread2, NULL, death_philo, data);
	pthread_detach(data->thread2);
	while (i < data->nb_philos)
	{
		if (pthread_create
			(&thread_id[i], NULL, &routine_func, &data->philo[i]) != 0)
		{
			printf("failed to create\n");
			return ;
		}
		i++;
	}
	data->tid = thread_id;
	return ;
}

void	end_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->tid[i], NULL);
		i++;
	}
}

void	destroy_and_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->print);
	free(data->forks);
	free(data->tid);
	free(data->philo);
}
