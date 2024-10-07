/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 01:25:04 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/20 12:31:33 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_bool(sem_t *semaphore, bool *dest, bool value)
{
    sem_wait(semaphore);   // Вход в критическую секцию
    *dest = value;         // Изменение значения
    sem_post(semaphore);   // Выход из критической секции
}

bool	get_bool(sem_t *semaphore, bool *value)
{
	bool	ret;

	sem_wait(semaphore);
	ret = *value;
	sem_post(semaphore);
	return (ret);
}

void 	set_long(sem_t *semaphore, long *dest, long value)
{
    sem_wait(semaphore);   // Вход в критическую секцию
    *dest = value;         // Изменение значения
    sem_post(semaphore);   // Выход из критической секции
}

long	get_long(sem_t *semaphore, long *value)
{
	long	ret;

	sem_wait(semaphore);
	ret = *value;
	sem_post(semaphore);
	return (ret);
}
bool	simulation_finished(t_table *table)
{
	return (get_bool(table->table_sem, &table->end_simulation));
}
