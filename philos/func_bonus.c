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

long	ft_atol(const char *str)
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

void	*monitor(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (!ph->stop)
	{
		usleep(100);
		if (get_time(MILLSEC) - ph->last_meal > ph->time_to_die)
		{
			ph->died = 1;
			sem_wait(ph->write);
			printf("%ld %d died\n", get_time(MILLSEC) - ph->start_time, ph->index);
			ph->stop = 1;
			break ;
		}
		if (ph->nbr_limit_meals != -1
			&& ph->meals_counter >= ph->nbr_limit_meals)
		{
			ph->stop = 1;
			break ;
		}
	}
		if (ph->died)
			error_exit("Philo died! 😢");
		else
			exit (0);
}
