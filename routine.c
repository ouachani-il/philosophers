/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilham_oua <ilham_oua@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:21:09 by ilham_oua         #+#    #+#             */
/*   Updated: 2023/12/18 19:55:52 by ilham_oua        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine_func(void *args)
{
    t_philo *philo;
    t_data  *data;

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

void    start_routine(t_data *data)
{
    pthread_t   *thread_id;
    int         i;
    int         status;

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
    
}
