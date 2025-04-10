/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:13:54 by alucas-e          #+#    #+#             */
/*   Updated: 2025/04/10 16:47:42 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	parse_args(int argc, char **argv, t_table *table)
{
	table->nbr_philos = (int)ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->nbr_meals = (int)ft_atol(argv[5]);
	else
		table->nbr_meals = -1;
}

int	validate_args(int argc, t_table *table)
{
	if (table->nbr_philos <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0
		|| (argc == 6 && table->nbr_meals <= 0))
	{
		printf("ERROR: Invalid argument (non-positive value)\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	parse_args(argc, argv, &table);
	if (validate_args(argc, &table))
		return (EXIT_FAILURE);
	init_table(&table);
	create_threads(&table);
	monitor(&table);
	join_threads(&table);
	clean(&table);
	return (EXIT_SUCCESS);
}
