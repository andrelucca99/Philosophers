/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:29:44 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/26 15:17:22 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_philosopher
{
	int				id;
	pthread_t		thread;
	long			last_meal;
	int				meals_eaten;
	struct s_table	*table;
} t_philosopher;

typedef struct s_table
{
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    t_philosopher *philosophers;
} t_table;

long current_time(void);
void init_table(t_table *table, int argc, char **argv);
void start_simulation(t_table *table);
void *philosopher_routine(void *arg);

#endif
