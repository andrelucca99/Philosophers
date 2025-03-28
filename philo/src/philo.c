/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:40:30 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/27 16:51:29 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	signal;

	i = 0;
	signal = 1;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signal *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		i *= 10;
		i += *str - '0';
		str++;
	}
	i *= signal;
	return (i);
}

void	init_table(t_table *table, int argc, char **argv)
{
	int	i;

	i = 0;
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	table->start_time = current_time();
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	table->philosophers = malloc(sizeof(t_philosopher) * table->num_philos);
	pthread_mutex_init(&table->print_mutex, NULL);
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		table->philosophers[i].id = i;
		table->philosophers[i].last_meal = table->start_time;
		table->philosophers[i].meals_eaten = 0;
		table->philosophers[i].table = table;
		i++;
	}
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;
	int		count;

	table = (t_table *)arg;
	while (1)
	{
		count = 0;
		i = 0;
		while (i < table->num_philos)
		{
			pthread_mutex_lock(&table->print_mutex);
			// Verifica se um filósofo morreu
			if ((current_time() - table->philosophers[i].last_meal) > table->time_to_die)
			{
				printf("%ld %d morreu\n", current_time() - table->start_time, table->philosophers[i].id);
				exit(0); // Encerra o programa quando um filósofo morre
			}
			// Verifica se todos comeram o suficiente
			if (table->must_eat > 0 && table->philosophers[i].meals_eaten >= table->must_eat)
				count++;
			pthread_mutex_unlock(&table->print_mutex);
			i++;
		}
		// Se todos os filósofos comeram o suficiente, encerramos o programa
		if (table->must_eat > 0 && count == table->num_philos)
		{
			printf("Todos os filósofos comeram o suficiente. Encerrando...\n");
			exit(0);
		}
		usleep(1000);
	}
	return (NULL);
}


void	start_simulation(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;

    // Criamos a thread que monitora se algum filósofo morreu
	pthread_create(&monitor_thread, NULL, monitor_routine, table);

    // Criamos as threads para cada filósofo
	while (i < table->num_philos)
	{
		pthread_create(&table->philosophers[i].thread,
			NULL, philosopher_routine, &table->philosophers[i]);
		i++;
	}

    // Esperamos todas as threads dos filósofos terminarem
	while (i < table->num_philos)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}

    // Esperamos a thread de monitoramento terminar
    pthread_join(monitor_thread, NULL);
}

