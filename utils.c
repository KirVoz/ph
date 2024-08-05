/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:59:42 by kvoznese          #+#    #+#             */
/*   Updated: 2024/07/29 20:01:44 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("GEttimeofday failed!");
	if (SEC == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLSEC == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSEC == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Awww... Wrong input...");
	return (555);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(MICROSEC);
	while (get_time(MICROSEC) - start < usec)
	{
		if (simulation_finished(table))
			break;
		elapsed = get_time(MICROSEC) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(usec / 2);
		else
		{
			while (get_time(MICROSEC) - start < usec)
				;
		}
	}
}

void	error_exit(const char *error)
{
	printf(RED "🚨 %s 😡\n" RESET, error);
	exit(EXIT_FAILURE);
}
