/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:48:18 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/22 17:14:51 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	value;
	int	sign;

	i = 0;
	value = 0;
	sign = 1;
	while ((nptr[i] >= 7 && nptr[i] <= 13) || nptr[i] == ' ' || &nptr[i] == 0)
		i++;
	if (nptr[i] == '-')
		sign *= -1;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-' && (nptr[i + 1] == '+' || nptr[i + 1] == '-'))
			return (0);
		else if (nptr[i] == '+' && (nptr[i + 1] == '-' || nptr[i + 1] == '+'))
			return (0);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		value = value * 10 + nptr[i] - '0';
		i++;
	}
	return (value * sign);
}
