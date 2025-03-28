/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:41:11 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/28 15:06:59 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_table			*table;
	int				think_time;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		usleep(10000);
	table = philo->table;
	think_time = table->time_to_die - table->time_to_eat - table->time_to_sleep;
	if (think_time > 5)
		think_time = 5;
	else if (think_time < 0)
		think_time = 0;
	while (1)
	{
		// Pega os garfos
		pthread_mutex_lock(&table->forks[philo->id]);
		pthread_mutex_lock(&table->forks[(philo->id + 1) % table->num_philos]);

		// Atualiza o tempo da última refeição e o contador de refeições
		pthread_mutex_lock(&table->print_mutex);
		philo->last_meal = current_time();
		philo->meals_eaten++;
		printf("%ld %d está comendo\n", current_time() - table->start_time, philo->id);
		pthread_mutex_unlock(&table->print_mutex);

		usleep(table->time_to_eat * 1000);

		// Solta os garfos
		pthread_mutex_unlock(&table->forks[philo->id]);
		pthread_mutex_unlock(&table->forks[(philo->id + 1) % table->num_philos]);

		// Dormir
		pthread_mutex_lock(&table->print_mutex);
		printf("%ld %d está dormindo\n", current_time() - table->start_time, philo->id);
		pthread_mutex_unlock(&table->print_mutex);
		usleep(table->time_to_sleep * 1000);

		// Pensar
		pthread_mutex_lock(&table->print_mutex);
		printf("%ld %d está pensando\n", current_time() - table->start_time, philo->id);
		pthread_mutex_unlock(&table->print_mutex);
		usleep(think_time * 1000);
	}
}

