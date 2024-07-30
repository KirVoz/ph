/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:59:51 by kvoznese          #+#    #+#             */
/*   Updated: 2024/07/30 15:04:56 by kvoznese         ###   ########.fr       */
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

# define RESET "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

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
	t_fork				*fork;
	t_philo				*philos;
}						t_table;
/*error*/
void					error_exit(const char *error);
/*parser*/
void					parse_input(t_table *table, char **av);
/*safe*/
void					*safe_malloc(size_t bytes);
/*safe_malloc*/
void					*safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
/*safe_thread*/
void					safe_thread_handle(pthread_t *thread,
							void *(foo)(void *), void *data, t_opcode opcode);
/*init*/
void					data_init(t_table *table);


#endif