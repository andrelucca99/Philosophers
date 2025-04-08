/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:53:46 by alucas-e          #+#    #+#             */
/*   Updated: 2025/04/08 17:05:43 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->nbr_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->meal_counter = 0;
		philo->right_fork = &table->forks[i];
		philo->left_fork = &table->forks[(i + 1) % table->nbr_philos];
		philo->table = table;
		philo->last_meal_time = table->start_time;
		safe_mutex(table, &philo->meal_mutex, INIT);
		i++;
	}
}

void	init_table(t_table *table)
{
	int	i;

	table->simulation_ended = 0;
	table->finished_meals = 0;
	table->start_time = get_time();
	safe_mutex(table, &table->write_mutex, INIT);
	safe_mutex(table, &table->sim_mutex, INIT);
	table->forks = (t_fork *)malloc((sizeof(t_fork) * table->nbr_philos));
	if (!table->forks)
		error_exit(table, "Malloc failed (forks)\n");
	i = -1;
	while (++i < table->nbr_philos)
	{
		safe_mutex(table, &table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	table->philos = (t_philo *)malloc((sizeof(t_philo) * table->nbr_philos));
	if (!table->philos)
	{
		while (i-- > 0)
			safe_mutex(table, &table->forks[i].fork, DESTROY);
		free(table->forks);
		error_exit(table, "Malloc failed (philos)\n");
	}
	init_philos(table);
}
