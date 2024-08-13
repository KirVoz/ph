/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:59:51 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/13 20:37:04 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RST "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

# define DEBUG_MODE 1

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef enum e_time_code
{
	SEC,
	MILLSEC,
	MICROSEC,
}						t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mtx				philo_mutex;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_sleep;
	long				time_to_eat;
	long				nbr_limit_meals;
	long				start_simulation;
	bool				end_simulation;
	bool				all_threads_ready;
	long				threads_running_nbr;
	pthread_t			monitor;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
	t_fork				*forks;
	t_philo				*philos;
}						t_table;
/*error*/
void					error_exit(const char *error);
/*time*/
long					get_time(t_time_code time_code);
/*precice time founder*/
void					precise_usleep(long usec, t_table *table);
/*parser*/
void					parse_input(t_table *table, char **av);
/*safe_malloc*/
void					*safe_malloc(size_t bytes);
/*safe_malloc*/
void					safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
/*safe_thread*/
void					safe_thread_handle(pthread_t *thread,
							void *(foo)(void *), void *data, t_opcode opcode);
/*init*/
void					data_init(t_table *table);
/*bool + long set func*/
void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					get_bool(t_mtx *mutex, bool *value);
void					set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);
bool					simulation_finished(t_table *table);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);
/*spinlock*/
void					wait_all_threads(t_table *table);
void					increase_long(t_mtx *mutex, long *value);
/*write*/
void					write_status(t_philo_status status, t_philo *philo,
							bool debug);
/*dinner*/
void					dinner_start(t_table *table);
void					*dinner_simulation(void *data);
/*monitor*/
void					*monitor_dinner(void *data);
/*clean*/
void					clean(t_table *table);
/*thinking*/
void					thinking(t_philo *philo, bool pre_sim);
/*de_synch*/
void					de_synchronize(t_philo *philo);

#endif