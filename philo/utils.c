/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:42:51 by ilouacha          #+#    #+#             */
/*   Updated: 2024/02/02 23:18:13 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(char *str, t_data *data, int id)
{
	printf("%lldms %d %s\n", (current_time() - data->start), id + 1, str);
}

long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	ft_usleep(int time, t_data *data)
{
	long	start_time;

	start_time = current_time();
	pthread_mutex_lock(&data->death);
	while (current_time() - start_time < time
		&& data->dead == false && data->full == false)
	{
		pthread_mutex_unlock(&data->death);
		usleep(time / 10);
		pthread_mutex_lock(&data->death);
	}
	pthread_mutex_unlock(&data->death);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && n > 0 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
