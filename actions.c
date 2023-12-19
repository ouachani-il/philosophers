/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:48:51 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/19 16:29:13 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print);
	if (data->dead == true || data->full == true || data->nb_philos == 1)
	{
		pthread_mutex_unlock(&data->print);
		return ;
	}
	print_action("is sleeping", data, philo->id);
	pthread_mutex_unlock(&data->print);
	ft_usleep(philo->time_to_sleep, data);
}

void	thinking(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->print);
	if (data->dead == true || data->full == true || data->nb_philos == 1)
	{
		pthread_mutex_unlock(&data->print);
		return ;
	}
	print_action("is thinking", data, philo->id);
	pthread_mutex_unlock(&data->print);
}

	/* we should :
	# mutex the first fork right
	# then mutex the second fork (left)
	# unlock mutex fork left
	# unlock mutex fork right
	=> we should check wheather the lasting time before lock 
	the second fork to not die
	them mutex the print fot print */

void	eating(t_philo *philo)
{
	t_data	*data;
	long	start_time;

	data = philo->data;
	start_time = current_time();
	pthread_mutex_lock(&data->forks[philo->id]);
	if (current_time() - start_time > data->time_to_die)
	{
		data->dead = true;
		pthread_mutex_unlock(&data->forks[philo->id]);
		// exit and free
	}
	if (data->dead == true || data->full == true || data->nb_philos == 1)
	{
		pthread_mutex_unlock(&data->forks[philo->id]);
		return ;
	}
	pthread_mutex_lock(&data->forks[(philo->id + 1) % data->nb_philos]);
	if (current_time() - start_time > data->time_to_die)
	{
		pthread_mutex_lock(data->dead);
		data->dead = true;
		pthread_mutex_unlock(data->dead);
		pthread_mutex_unlock(&data->forks[philo->id]);
		// exit and free
	}
	if (data->dead == true || data->full == true || data->nb_philos == 1)
	{
		pthread_mutex_unlock(&data->forks[philo->id]);
		return ;
	}
	pthread_mutex_lock(&data->print);
	if (data->dead == true || data->full == true || data->nb_philos == 1)
	{
		pthread_mutex_unlock(&data->print);
		return ;
	}
	print_action("is eating", data, philo->id);
	pthread_mutex_unlock(&data->print);
	ft_usleep(philo->time_to_eat, data);
	pthread_mutex_unlock(&data->forks[philo->id]);
	pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->nb_philos]);
}

