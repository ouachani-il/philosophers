/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:41:03 by ilouacha          #+#    #+#             */
/*   Updated: 2024/02/02 21:10:03 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
				return (printf("Enter 5 or 6 digits superior to 0\n"), 1);
			j++;
		}
		if (ft_strncmp(av[i], "0", 1) == 0 && i != ac - 1)
			return (printf("Enter only integers superior to 0\n"), 1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac > 6 || ac < 5)
		return (printf("incorrect arguments number"), 0);
	if ((ft_strncmp(av[ac - 1], "0", 1) == 0 && ac == 6))
		return (printf("Philosophers don't need to eat\n"), 0);
	if (ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_parse(ac, av) == 1)
		return (0);
	init_data(&data, ac, av);
	init_mutex(&data);
	init_philos(&data);
	start_routine(&data);
	end_routine(&data);
	destroy_and_free(&data);
	exit(0);
	return (0);
}
