/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:42:35 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/20 13:03:43 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_exit("MALLOC ERROR!");
	return (ret);
}

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed!");
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
			break ;
		elapsed = get_time(MICROSEC) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (get_time(MICROSEC) - start < usec)
				;
		}
	}
}

static int	num_len(const int num)
{
	int	i;
	int	n;
	
	i = 0;
	n = num;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int num)
{
	char	*s;
	int		i;
	
	i = num_len(num);
	s = safe_malloc(sizeof(char)* (i + 1));
	if (!s)
		error_exit("Malloc can't be done");
	s[i] = '\0';
	if (num == 0)
		s[0] = '0';
	while (i > 0)
	{
		s[--i] = (num % 10) + '0';
		num = num / 10; 
	}
	return (s);
}
