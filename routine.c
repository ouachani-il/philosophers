/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:21:09 by ilham_oua         #+#    #+#             */
/*   Updated: 2023/12/19 19:50:51 by ilouacha         ###   ########.fr       */
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

void	start_routine(t_data *data)
{
	pthread_t	*thread_id;
	int		i;
	int		status;

	i = 0;
	status = 0;
	thread_id = malloc(sizeof(pthread_t) * data->nb_philos);
	data->start = current_time();
	pthread_create(&data->thread2, NULL, death_philo, data);
	pthread_detach(data->thread2);
	while (i < data->nb_philos)
	{
		if (pthread_create(&thread_id[i], NULL, &routine_func, &data->philo[i]) != 0)
		{
	
		}
	}
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
			if (current_time() - data->philo[i].time_last_meal > data->time_to_die
					&& data->full == false)
			{
				pthread_mutex_lock(&data->print);
				if (data->nb_philos == 1)
					pthread_mutex_unlock(&data->forks)
			}
		}
	}
}
