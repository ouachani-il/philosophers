/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilouacha <ilouacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:41:03 by ilouacha          #+#    #+#             */
/*   Updated: 2023/12/18 15:02:52 by ilouacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parse(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (i < ac)
	{
		j = 0;
		while ( j < (int)ft_strlen(av[i]))
		{
			if (!(av[i][j] <= 57 && av[i][j] >= 48))
				return (printf("Enter 5 or 6 digits superior to 0\n"), 1);
			j++;
		}
		if (ft_strncmp(av[i], "0", 1) == 0 && i != ac - 1)
			return (printf("Enter only integers superior to 0\n", 1));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac > 6 || ac < 5)
		return (printf("incorrect arguments numbers"), 0);
	if (ft_strncmp(av[ac - 1], "0", 1) == 0)
		return (printf("Philosophers don't need to eat\n"), 0);
	if (ft_parse(ac, av) == 1)
		return (0);
	init_data(&data, ac, av);
	init_mutex(&data);
	init_philo(&data);
	

}