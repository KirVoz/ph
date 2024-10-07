/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sinchro_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:37:47 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/20 13:01:19 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(table->table_sem, &table->all_threads_ready))
		;
}

bool	all_threads_running(sem_t *semaphore, long *threads,
		long philo_nbr)
{
	bool	ret;

	ret = false;
	sem_wait(semaphore);
	if (*threads == philo_nbr)
		ret = true;
	sem_post(semaphore);
	return (ret);
}

void	increase_long(sem_t *semaphore, long *value)
{
	sem_wait(semaphore);
	(*value)++;
	sem_post(semaphore);
}

void	de_synchronize(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}
