#include "philo_bonus.h"

void	clean(t_philo **philo)
{
	t_philo	*tmp;
	int		i;
	int		status;

	tmp = *philo;
	i = 0;
	while (i < tmp->philo_nbr)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < tmp->philo_nbr)
				kill(tmp->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(tmp->write);
	sem_close(tmp->forks);
	sem_unlink("write");
	sem_unlink("forks");
	free(tmp->pid);
	free(tmp);
}

size_t	get_time(t_time_code time_code)
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

void	precise_usleep(long usec, t_philo *philo)
{
	size_t	t;

	t = get_time(MILLSEC);
	while (!philo->stop)
	{
		if (get_time(MILLSEC) - t >= usec)
			break ;
		usleep(500);
	}
}

void	error_exit(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void print_status(t_philo *philo, char *status)
{
	sem_wait(philo->write);
	if (!philo->stop)
		printf("time:%ld philo:%d %s\n", get_time(MILLSEC) - philo->start_time, philo->index, status);
	sem_post(philo->write);
}
