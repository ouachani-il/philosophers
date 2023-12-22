/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:41:03 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/22 20:58:43 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_parse(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (j < (int)ft_strlen(av[i]))
		{
			if (!(av[i][j] <= 57 && av[i][j] >= 48))
				return (printf("Enter 4 or 5 digits superior to 0\n"), 1);
			j++;
		}
		if (ft_strncmp(av[i], "0", 1) == 0 && i != ac - 1)
			return (printf("Enter 4 or 5 digits superior to 0\n"), 1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac > 6 || ac < 5)
		return (printf("Enter 4 or 5 digits superior to 0\n"), 0);
	if (ft_strncmp(av[ac - 1], "0", 1) == 0)
		return (printf("Philosophers don't need to eat\n"), 0);
	if (ft_parse(ac, av) == 1)
		return (1);
	init_data(&data, ac, av);
	init_semaphores(&data);
	start_routine(&data);
	kill_process(&data);
	return (0);
}
