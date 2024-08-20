/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:48:14 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/20 14:25:59 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	thinking(t_philo *philo, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;
	
	if (!pre_sim)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->t2e;
	t_sleep = philo->table->t2s;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(philo->philo_sem, &philo->last_meal_time, get_time(MILLSEC));
	increase_long(philo->table->table_sem,
		&philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		usleep(200);
		return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_sem_handle(philo->first_fork->fork, WAIT);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_sem_handle(philo->second_fork->fork, WAIT);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(philo->philo_sem, &philo->last_meal_time, get_time(MILLSEC));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->t2e, philo->table);
	if (philo->table->meals_to_eat > 0
		&& philo->meals_counter == philo->table->meals_to_eat)
		set_bool(philo->philo_sem, &philo->full, true);
	safe_sem_handle(philo->first_fork->fork, POST);
	safe_sem_handle(philo->second_fork->fork, POST);
}

static void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(philo->philo_sem, &philo->last_meal_time,
		get_time(MILLSEC));
	increase_long(philo->table->table_sem,
		&philo->table->threads_running_nbr);
	de_synchronize(philo);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->t2s, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->meals_to_eat == 0)
		return ;
	else if (table->philo_nbr == 1)
		safe_thread_handle(&table->philos[0].thread_id, lone_philo,
		&table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitoring, monitoring_dinner, table, CREATE);
	table->start_simulation = get_time(MILLSEC);
	set_bool(table->table_sem, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(table->table_sem, &table->end_simulation, true);
	safe_thread_handle(&table->monitoring, NULL, NULL, JOIN);
}
