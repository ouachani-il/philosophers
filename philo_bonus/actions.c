/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:48:51 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/22 20:59:52 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sleep_think(t_data *data)
{
	sem_wait(data->print);
	print_action("is sleeping", data, data->philo.id);
	sem_post(data->print);
	ft_usleep(data->time_to_sleep);
	sem_wait(data->print);
	print_action("is thinking", data, data->philo.id);
	sem_post(data->print);
}

void	eating(t_data *data)
{
	sem_wait(data->forks);
	sem_wait(data->print);
	print_action("has taken a fork", data, data->philo.id);
	if (data->nb_philos == 1)
	{
		sem_post(data->forks);
		sem_post(data->print);
		return ;
	}
	sem_wait(data->forks);
	print_action("has taken a fork", data, data->philo.id);
	print_action("has taken a fork", data, data->philo.id);
	sem_post(data->print);
	data->philo.time_last_meal = current_time();
	data->philo.nb_meals += 1;
	if (data->philo.nb_meals == data->nb_meals)
		sem_post(data->full);
	ft_usleep(data->time_to_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}
