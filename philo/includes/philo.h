/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:02:45 by alucas-e          #+#    #+#             */
/*   Updated: 2025/04/11 17:25:03 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_mode
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mode;

typedef struct s_table	t_table;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				meal_counter;
	unsigned long	last_meal_time;
	t_table			*table;
	t_fork			*right_fork;
	t_fork			*left_fork;
	pthread_t		thread_id;
	pthread_mutex_t	meal_mutex;
}	t_philo;

typedef struct s_table
{
	int				nbr_philos;
	int				nbr_meals;
	int				simulation_ended;
	int				finished_meals;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	unsigned long	start_time;
	pthread_t		monitor;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	sim_mutex;
	t_fork			*forks;
	t_philo			*philos;
}	t_table;

int				validate_args(int argc, t_table *table);
void			parse_args(int argc, char **argv, t_table *table);

void			init_table(t_table *table);

unsigned long	get_time(void);
long			ft_atol(char *str);
void			error_exit(t_table *table, char *error);
void			print_message(t_philo *philo, char *msg);
int				ft_strcmp(const char *s1, const char *s2);

void			handle_mutex_errors(int status, t_mode mode);
void			safe_mutex(t_table *table, pthread_mutex_t *mutex, t_mode mode);

void			join_threads(t_table *table);
void			create_threads(t_table *table);

void			*routine(void *arg);
void			*one_philo(void *arg);
void			take_forks(t_philo *philo);
void			eat_sleep_think(t_philo *philo);

void			clean(t_table *table);

void			monitor(t_table *table);
int				check_all_meals(t_table *table);
int				check_philo_death(t_philo *philo, long time_to_die);

#endif