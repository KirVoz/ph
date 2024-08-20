/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:21:57 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/20 14:03:56 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		philo->philo_sem_name = ft_itoa(i + 1);
		sem_unlink(philo->philo_sem_name);
		philo->philo_sem = sem_open(philo->philo_sem_name, O_CREAT | O_RDWR, 0777, 1);
		assign_forks(philo, table->forks, i);
	}
}

static void	start_semaphores(t_table *table)
{
	sem_unlink("/write_print");
	sem_unlink("/table_sem");
	table->table_sem = sem_open("/table_sem", O_CREAT | O_RDWR, 0777, 1);
	table->write_sem = sem_open("/write_sem", O_CREAT | O_RDWR, 0777, 1);
}

void	init(t_table *table)
{
	int		i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->threads_running_nbr = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	start_semaphores(table);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (++i < table->philo_nbr)
	{
		table->forks[i].sem_name = ft_itoa(i);
		sem_unlink(table->forks[i].sem_name);
		table->forks[i].fork = sem_open(table->forks[i].sem_name, O_CREAT |
			O_RDWR, 0777, 1);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
