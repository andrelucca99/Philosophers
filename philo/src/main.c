/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:29:48 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/26 15:16:40 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		printf("Uso: ./philo num_philos time_to_die time_to_eat time_to_sleep [must_eat]\n");
		return (1);
	}
	init_table(&table, argc, argv);
	start_simulation(&table);
	return (0);
}
