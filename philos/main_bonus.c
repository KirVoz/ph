#include "philo_bonus.h"

static void life_cycle(t_philo *philo)
{
	if (pthread_create(&philo->referi, NULL, monitor, philo))
		error_exit("Thread creation failed! 😢");
	if (philo->index % 2 == 1)
		precise_usleep(1e3, philo);
	while (1)
	{
		sem_wait(philo->forks);
		print_status(philo, "has taken a fork");
		sem_wait(philo->forks);
		print_status(philo, "has taken a fork");
		print_status(philo, "is eating");
		philo->last_meal = get_time(MILLSEC);
		precise_usleep(philo->time_to_eat, philo);
		sem_post(philo->forks);
		sem_post(philo->forks);
		philo->meals_counter++;
		print_status(philo, "is sleeping");
		precise_usleep(philo->time_to_sleep, philo);
		print_status(philo, "is thinking");
	}
	if (pthread_join(philo->referi, NULL))	
		error_exit("Thread join failed! 😢");
}

static void start_simulation(t_philo *table)
{
	int	i;

	table->start_time = get_time(MILLSEC);
	table->pid = (int *)malloc(sizeof(int) * table->philo_nbr);
	i = -1;
	while (++i < table->philo_nbr)
	{
		table->pid[i] = fork();
		if (table->pid[i] == -1)
			error_exit("Fork failed! 😢");
		if (table->pid[i] == 0)
		{
			table->index = i + 1;
			table->last_meal = get_time(MILLSEC);
			life_cycle(table);
			clean(&table);
		}
	}
}

static int	parse_init(t_philo *table, char **av)
{
	table->philo_nbr = ft_atol(av[1]);
	table->forks_nbr = table->philo_nbr;
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		return (1);
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
	sem_unlink("forks");
	sem_unlink("write");
	table->write = sem_open("write", O_CREAT, 0644, 1);
	if (table->write == SEM_FAILED)
		return (2);
	table->forks = sem_open("forks", O_CREAT, 0644, table->forks_nbr);
	if (table->forks == SEM_FAILED)
		return (2);
	table->meals_counter = 0;
	table->died = 0;
	table->stop = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	table;

	if (ac < 5 || ac > 6)
		error_exit("Wrong number of arguments!");
	if (parse_init(&table, av) == 1)
		error_exit("⏲ USE TIMESTAMPS MAJOR THAN 60MS 🕰");
	else if (parse_init(&table, av) == 2)
		error_exit("Semaphore initialization failed! 😢");
	start_simulation(&table);
	return (0);
}
