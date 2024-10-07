/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 08:06:52 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/20 13:00:37 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t2d;
	
	if (get_bool(philo->philo_sem, &philo->full))
		return (false);
	elapsed = get_time(MILLSEC) - get_long(philo->philo_sem,
			&philo->last_meal_time);
	t2d = philo->table->t2d / 1e3;
	if (elapsed > t2d)
		return (true);
	return (false);
}

void	*monitoring_dinner(void *data)
{
	int	i;
	t_table	*table;
	
	table = (t_table *)data;
	while (!all_threads_running(table->table_sem,
			&table->threads_running_nbr, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(table->table_sem, &table->end_simulation, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);	
}
