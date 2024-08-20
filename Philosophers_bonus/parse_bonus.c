/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvoznese <kvoznese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:57:30 by kvoznese          #+#    #+#             */
/*   Updated: 2024/08/20 13:08:29 by kvoznese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("😱 ONLY POSITIVE NUMBERS 🥺");
	if (!is_digit(*str))
		error_exit("🤪 THIS IS NON A NUMBER 🤨");
	number = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		error_exit("😰 MORE THAN INT_MAX LIMIT 😩");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = num * 10 + (*str++ - '0');
	if (num > INT_MAX)
		error_exit("😰 MORE THAN INT_MAX LIMIT 😩");
	return (num);
}

void	parse(t_table *philo, char **av)
{
	philo->philo_nbr = ft_atol(av[1]);
	philo->t2d = ft_atol(av[2]) * 1e3;
	philo->t2e = ft_atol(av[3]) * 1e3;
	philo->t2s = ft_atol(av[4]) * 1e3;
	if (philo->t2d < 6e4
		|| philo->t2e < 6e4
		|| philo->t2s < 6e4)
		error_exit(RED"⏲ USE TIMESTAMPS MAJOR THAN 60MS 🕰");
	if (av[5])
		philo->meals_to_eat = ft_atol(av[5]);
	else
		philo->meals_to_eat = -1;
}
