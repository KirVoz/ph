/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:30:01 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/08 15:11:58 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_debug(t_philo_status status, t_philo *philo,
		long elapsed)
{
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
		printf(WHITE"%6ld"RST" %d has taken 1st fork"
			"\t\t\tn" BLUE "[...%d...]\n" RST,
			elapsed,
			philo->id,
			philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
		printf(WHITE "%6ld" RST " %d has taken 2nd fork"
			"\t\t\tn" BLUE "[...%d...]\n" RST,
			elapsed,
			philo->id,
			philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(WHITE "%6ld" CYAN " %d is eating"
			"\t\t\t" YELLOW "[...%ld...]\n" RST,
			elapsed,
			philo->id,
			philo->meals_counter);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(WHITE "%6ld" RST " %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(WHITE "%6ld" RST " %d is thinking\n", elapsed, philo->id);
	else if (DIED == status && !simulation_finished(philo->table))
		printf(RED "\t\t\t %6ld %d is dead....\n" RST, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILLSEC) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& (!simulation_finished(philo->table)))
			printf(WHITE "%-6ld" RST " %d has taken a fork\n", elapsed,
				philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(WHITE "%-6ld" CYAN " %d is eating\n" RST, elapsed,
				philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf(WHITE "%-6ld" RST " %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf(WHITE "%-6ld" RST " %d is thinking\n", elapsed, philo->id);
		else if (DIED == status && !simulation_finished(philo->table))
			printf(WHITE "%-6ld" RST " %d DIED\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
