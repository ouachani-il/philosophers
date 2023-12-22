/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:48:51 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/22 15:58:35 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->nb_philos]);
	pthread_mutex_unlock(&data->forks[philo->id]);
}

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

void	eating_suite(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	philo->nb_meals += 1;
	if (philo->nb_meals == data->nb_meals)
		data->belly += philo->nb_meals;
	if (data->belly == data->all_full)
	{
		release_forks(philo);
		data->full = true;
		printf("All philosophers have eaten\n");
		pthread_mutex_unlock(&data->print);
		return ;
	}
	pthread_mutex_unlock(&data->print);
	ft_usleep(philo->time_to_eat, data);
	release_forks(philo);
}

void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->id]);
	pthread_mutex_lock(&data->print);
	if (data->dead == true || data->full == true)
	{
		pthread_mutex_unlock(&data->forks[philo->id]);
		pthread_mutex_unlock(&data->print);
		return ;
	}
	print_action("has taken a fork", data, philo->id);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(&data->forks[(philo->id + 1) % data->nb_philos]);
	pthread_mutex_lock(&data->print);
	if (data->dead == true || data->full == true)
	{
		release_forks(philo);
		pthread_mutex_unlock(&data->print);
		return ;
	}
	print_action("has taken a fork", data, philo->id);
	print_action("is eating", data, philo->id);
	philo->time_last_meal = current_time();
	eating_suite(philo);
}
