/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:48:51 by ilouacha          #+#    #+#             */
/*   Updated: 2024/02/02 23:50:50 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	get_death(t_data *data)
// {
// 	pthread_mutex_lock(&data->death);
// 	return
// 	pthread_mutex_unlock(&data->death);
	
// }



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
	pthread_mutex_lock(&data->death);
	if (data->dead == true || data->full == true || data->nb_philos == 1)
	{
		pthread_mutex_unlock(&data->death);
		return ;
	}
	pthread_mutex_unlock(&data->death);
	pthread_mutex_lock(&data->print);
	print_action("is sleeping", data, philo->id);
	pthread_mutex_unlock(&data->print);
	ft_usleep(philo->time_to_sleep, data);
}

void	thinking(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->death);
	if (data->dead == true || data->full == true || data->nb_philos == 1)
	{
		pthread_mutex_unlock(&data->death);
		return ;
	}
	pthread_mutex_unlock(&data->death);
	pthread_mutex_lock(&data->print);
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
		pthread_mutex_lock(&data->print);
		printf("All philosophers have eaten\n");
		pthread_mutex_unlock(&data->print);
		return ;
	}
	ft_usleep(philo->time_to_eat, data);
	release_forks(philo);
}

void	lock_forks(t_philo *philo, int first, int second)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[first]);
	pthread_mutex_lock(&data->death);
	if (data->dead == true || data->full == true)
	{
		pthread_mutex_unlock(&data->death);
		pthread_mutex_unlock(&data->forks[first]);
		return ;
	}
	pthread_mutex_unlock(&data->death);
	pthread_mutex_lock(&data->print);
	print_action("has taken a fork", data, first);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(&data->forks[second]);
	pthread_mutex_lock(&data->death);
	if (data->dead == true || data->full == true)
	{
		pthread_mutex_unlock(&data->death);
		release_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&data->death);
	pthread_mutex_lock(&data->print);
	print_action("has taken a fork", data, philo->id);
	print_action("is eating", data, philo->id);
	pthread_mutex_unlock(&data->print);
	philo->time_last_meal = current_time();

}

void	eating(t_philo *philo)// t_fork *first_fork, t_fork second_fork
//(philo->id + 1) % data->nb_philos
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		lock_fork(philo, philo->id);
		lock_fork(philo, (philo->id + 1) % data->nb_philos);
	}
	else
	{
		lock_fork(philo, (philo->id + 1) % data->nb_philos);
		lock_fork(philo, philo->id);
	}
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->id]);
	pthread_mutex_lock(&data->death);
	if (data->dead == true || data->full == true)
	{
		pthread_mutex_unlock(&data->death);
		pthread_mutex_unlock(&data->forks[philo->id]);
		return ;
	}
	pthread_mutex_unlock(&data->death);
	pthread_mutex_lock(&data->print);
	print_action("has taken a fork", data, philo->id);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_lock(&data->forks[(philo->id + 1) % data->nb_philos]);
	pthread_mutex_lock(&data->death);
	if (data->dead == true || data->full == true)
	{
		pthread_mutex_unlock(&data->death);
		release_forks(philo);
		return ;
	}
	pthread_mutex_unlock(&data->death);
	pthread_mutex_lock(&data->print);
	print_action("has taken a fork", data, philo->id);
	
	pthread_mutex_lock(&data->print);
	print_action("is eating", data, philo->id);
	pthread_mutex_unlock(&data->print);
	philo->time_last_meal = current_time();
	eating_suite(philo);
}
