/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 20:39:00 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/22 20:39:29 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		kill(data->philo_id[i], SIGKILL);
		i++;
	}
	sem_close(data->death);
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->full);
	free(data->philo_id);
}
