/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:00:13 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/13 21:16:58 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ./philo 5 800 200 200 [5]*/
int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		parse_input(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
		system("leaks philo");
	}
	else
	{
		error_exit("Wrong input:\n" GREEN
			"Correct is ./philo num num num num [num]" RST);
	}
}
