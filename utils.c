/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:42:51 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/15 23:21:06 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(char *str, t_data *data, int id)
{
	printf("%lldms %d %s\n", current_time() - data->start, id, str)
}

long long	current_time()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((long long) (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
