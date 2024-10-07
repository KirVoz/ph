/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:54:52 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/20 14:54:13 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	clean(t_table *table)
{
    t_philo	*philo;
    int		i;

    i = -1;
    while (++i < table->philo_nbr)
    {
        philo = table->philos + i;
        safe_sem_handle(table->forks[i].fork, CLOSE);
        sem_unlink(table->forks[i].sem_name);
    }
    safe_sem_handle(table->table_sem, CLOSE);
    sem_unlink("table_sem");
    safe_sem_handle(table->write_sem, CLOSE);
    sem_unlink("write_sem");
    free(table->forks);
    free(table->philos);
}

void	error_exit(const char *error)
{
	printf(RED "🚨 %s 😡\n" RST, error);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_table	philo;

	if (ac == 5 || ac == 6)
	{
		parse(&philo, av);
		init(&philo);
		dinner(&philo);
		clean(&philo);
	}
	else
		error_exit(YELLOW"Wrong input"RST);
}
