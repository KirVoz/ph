/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 06:07:19 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/20 14:06:08 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>    //| WRITE, USLEEP
# include <stdlib.h>    //| MALLOC, FREE, NULL
# include <pthread.h>   //| THREAD's FUNCTIONS
# include <stdio.h>     //| PRINTF
# include <sys/time.h>  //| GETTIMEOFDAY
# include <sys/wait.h>  //| WAITPID
# include <fcntl.h>     //| PERMISSIONS
# include <semaphore.h> //| SEM_T, SEM_UNLINK, SEM_OPEN, SEM_CLOSE
# include <signal.h>    //| MACROS
# include <limits.h>    //| INT_MAX
# include <stdbool.h>	//| BOOL
# include <errno.h>		//| ERRNO

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
	JOIN,
	DETACH,
	CREATE,
	OPEN,
	CLOSE,
	POST,
	WAIT,
	UNLINK,
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

typedef struct s_table	t_table;

typedef struct 	s_fork
{
	sem_t	*fork;
	int		fork_id;
	char	*sem_name;
}				t_fork;


typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	sem_t		*philo_sem;
	char		*philo_sem_name;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	long		philo_nbr;
	long		t2d;
	long		t2e;
	long		t2s;
	long		meals_to_eat;
	long		start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	long		threads_running_nbr;
	pthread_t	monitoring;
	sem_t		*write_sem;
	sem_t		*table_sem;
	t_fork		*forks;
	t_philo		*philos;
}				t_table;

/*error*/
void	error_exit(const char *error);
/*utils*/
void	precise_usleep(long usec, t_table *table);
long	get_time(t_time_code time_code);
void	*safe_malloc(size_t bytes);
char	*ft_itoa(int num);
/*parse*/
void	parse(t_table *philo, char **av);
/*safe_thread*/
void	safe_thread_handle(pthread_t *thread, void *(foo)(void *), void *data,
		t_opcode opcode);
/*safe_sem_test*/
void	safe_sem_handle(sem_t *semaphore, t_opcode opcode);
/*init*/
void	init(t_table *table);
/*getters_setters_bonus*/
void	set_bool(sem_t *semaphore, bool *dest, bool value);
bool	get_bool(sem_t *semaphore, bool *value);
void 	set_long(sem_t *semaphore, long *dest, long value);
long	get_long(sem_t *semaphore, long *value);
bool	simulation_finished(t_table *table);
/*sinchro*/
void	wait_all_threads(t_table *philo);
bool	all_threads_running(sem_t *semaphore, long *threads,
		long philo_nbr);
void	increase_long(sem_t *semaphore, long *value);
void	de_synchronize(t_philo *philo);
/*write*/
void	write_status(t_philo_status status, t_philo *philo, bool debug);
/*monitoring*/
void	*monitoring_dinner(void *data);
/*dinner*/
void	dinner(t_table *table);
void	thinking(t_philo *philo, bool pre_sim);
void	*lone_philo(void *data);
#endif