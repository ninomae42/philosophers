#include "philosophers.h"

sem_t	*philo_semaphore;
sem_t	*syslog_sem;
sem_t	*fork_sem;
bool	is_simulation_stop = false;
bool	is_running = false;
size_t	eat_cnt = 0;
t_time	last_eat_in_usec;
int	time_to_die = 310;
int	time_to_eat = 200;
int	time_to_sleep = 100;
int	min_eat_cnt = 5;

int	print_syslog(char *msg)
{
	sem_wait(syslog_sem);
	if (is_simulation_stop)
	{
		sem_post(syslog_sem);
		return (1);
	}
	printf("%s\n", msg);
	sem_post(syslog_sem);
	return (0);
}

void	*philo_routine(void *arg)
{
	last_eat_in_usec = get_current_time_in_usec();
	is_running = true;
	while (eat_cnt < min_eat_cnt)
	{
		sem_wait(fork_sem);
		if (print_syslog("[philo] taken a fork") != 0)
			break ;

		sem_wait(fork_sem);
		if (print_syslog("[philo] taken a fork") != 0)
			break ;

		last_eat_in_usec = get_current_time_in_usec();
		eat_cnt++;
		if (print_syslog("[philo] is eating") != 0)
			break ;
		ft_msleep(time_to_eat);

		sem_post(fork_sem);
		sem_post(fork_sem);

		if (print_syslog("[philo] is sleeping") != 0)
			break ;
		ft_msleep(time_to_sleep);

		if (print_syslog("[philo] is thinking") != 0)
			break ;

	}
	sem_wait(syslog_sem);
	printf("[philo] return\n");
	sem_post(syslog_sem);
	return (arg);
}

t_time	get_time_difference_in_msec(t_time current)
{
	t_time	difference;

	difference = get_current_time_in_usec() - current;
	difference /= USEC_TO_MSEC;
	return (difference);
}

void	*monitor_routine(void *arg)
{
	while (1)
	{
		if (min_eat_cnt <= eat_cnt)
			break ;
		if (is_running && time_to_die <= get_time_difference_in_msec(last_eat_in_usec))
		{
			sem_wait(syslog_sem);
			printf("[monitor] philo died\n");
			is_simulation_stop = true;
			sem_post(syslog_sem);
			break ;
		}
		ft_msleep(50);
	}
	sem_wait(syslog_sem);
	printf("[monitor] return\n");
	sem_post(syslog_sem);
	return (arg);
}

int	main(void)
{
	pthread_t	philo1;
	pthread_t	philo2;
	pthread_t	monitor;

	philo_semaphore = sem_open("/sem_philo", SEM_OFLAG, SEM_MODE, 1);
	if (philo_semaphore == SEM_FAILED)
	{
		perror("Unable to create and open semaphore");
		exit(EXIT_FAILURE);
	}
	syslog_sem = sem_open("/sem_syslog", SEM_OFLAG, SEM_MODE, 1);
	if (syslog_sem == SEM_FAILED)
	{
		perror("Unable to create and open semaphore");
		exit(EXIT_FAILURE);
	}
	fork_sem = sem_open("/sem_fork", SEM_OFLAG, SEM_MODE, 2);
	if (syslog_sem == SEM_FAILED)
	{
		perror("Unable to create and open semaphore");
		exit(EXIT_FAILURE);
	}

	if (pthread_create(&monitor, NULL, &monitor_routine, NULL) != 0)
	{
		perror("Unable to create monitor thread");
		exit(EXIT_FAILURE);
	}
	if (pthread_create(&philo1, NULL, &philo_routine, NULL) != 0)
	{
		perror("Unable to create philo1 thread");
		exit(EXIT_FAILURE);
	}
	// if (pthread_create(&philo2, NULL, &philo_routine, NULL) != 0)
	// {
	// 	perror("Unable to create philo1 thread");
	// 	exit(EXIT_FAILURE);
	// }

	pthread_join(monitor, NULL);
	pthread_join(philo1, NULL);
	// pthread_join(philo2, NULL);

	if (sem_close(philo_semaphore) != 0)
		perror("Unable to close semaphore");
	if (sem_unlink("/sem_philo") != 0)
		perror("Unable to unlink semaphore");
	if (sem_close(syslog_sem) != 0)
		perror("Unable to close semaphore");
	if (sem_unlink("/sem_syslog") != 0)
		perror("Unable to unlink semaphore");
	if (sem_close(fork_sem) != 0)
		perror("Unable to close semaphore");
	if (sem_unlink("/sem_fork") != 0)
		perror("Unable to unlink semaphore");
	exit(EXIT_SUCCESS);
}