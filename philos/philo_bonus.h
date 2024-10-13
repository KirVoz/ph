#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include "semaphore.h"
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>


typedef enum 			e_time_code
{
	SEC,
	MILLSEC,
	MICROSEC,
}						t_time_code;

typedef struct 			s_philo
{
	size_t				philo_nbr;
	size_t				forks_nbr;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					nbr_limit_meals;
	int					meals_counter;
	int					stop;
	int 				died;
	int					*pid;
	sem_t				*forks;
	sem_t				*write;
	size_t				start_time;
	int					index;
	size_t				last_meal;
	pthread_t			referi;
}						t_philo;

// utils_bonus.c
size_t					get_time(t_time_code time_code);
void					print_status(t_philo *philo, char *status);
void					error_exit(char *str);
void					precise_usleep(long usec, t_philo *philo);
void					clean(t_philo **philo);
// func_bonus.c
long					ft_atol(const char *str);
void					*monitor(void *philo);
#endif
