#include "philo_bonus.h"

# define FT_SEM_OFLAG (O_CREAT | O_EXCL)
# define FT_SEM_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
# define MAX_RES 2000000
# define FT_SEM_NAME "/semtest"
# define FT_SEM_LOG "/semtest_log"
# define FT_SEM_FORK "/semtest_fork"

int	print_log(t_philo *philo, t_log_type log_type, t_time log_time)
{
	if (sem_wait(philo->access_sem) < 0)
		perror("sem_wait");
	if (philo->is_simulation_stop)
	{
		if (sem_post(philo->access_sem) < 0)
			perror("sem_post");
		return (-1);
	}
	if (sem_post(philo->access_sem) < 0)
		perror("sem_post");
	if (sem_wait(philo->log_sem) < 0)
		perror("sem_wait");
	if (log_type == LOG_FORK)
		printf("%lld philo has taken a fork\n",
				log_time);
	else if (log_type == LOG_EAT)
		printf("%lld philo is eating\n",
				log_time);
	else if (log_type == LOG_SLEEP)
		printf("%lld philo is sleeping\n",
				log_time);
	else if (log_type == LOG_THINK)
		printf("%lld philo is thinking\n",
				log_time);
	if (sem_post(philo->log_sem) < 0)
		perror("sem_post");
	return (0);
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	printf("Philo thread craeted\n");
	philo = (t_philo *)args;
	if (sem_wait(philo->access_sem) < 0)
		perror("sem_wait");
	philo->time_last_eat = get_current_time_in_msec();
	if (sem_post(philo->access_sem) < 0)
		perror("sem_wait");
	while (1)
	{
		if (sem_wait(philo->fork_left_sem) < 0)
			perror("sem_wait");
		if (print_log(philo, LOG_FORK, get_current_time_in_msec()) < 0)
		{
			if (sem_post(philo->fork_left_sem) < 0)
				perror("sem_post");
			break ;
		}

		if (sem_wait(philo->fork_right_sem) < 0)
			perror("sem_wait");
		if (print_log(philo, LOG_FORK, get_current_time_in_msec()) < 0)
		{
			if (sem_post(philo->fork_right_sem) < 0)
				perror("sem_post");
			if (sem_post(philo->fork_left_sem) < 0)
				perror("sem_post");
			break ;
		}

		if (sem_wait(philo->access_sem) < 0)
			perror("sem_wait");
		if (philo->num_of_must_eat != 0 && philo->num_of_must_eat <= philo->num_of_current_eat)
		{
			philo->is_simulation_stop = true;
			if (sem_post(philo->access_sem) < 0)
				perror("sem_post");
			if (sem_post(philo->fork_right_sem) < 0)
				perror("sem_post");
			if (sem_post(philo->fork_left_sem) < 0)
				perror("sem_post");
			break ;
		}
		philo->time_last_eat = get_current_time_in_msec();
		philo->num_of_current_eat++;
		if (sem_post(philo->access_sem) < 0)
			perror("sem_post");
		print_log(philo, LOG_EAT, philo->time_last_eat);
		ft_msleep(philo->time_to_eat);

		if (sem_post(philo->fork_right_sem) < 0)
			perror("sem_post");
		if (sem_post(philo->fork_left_sem) < 0)
			perror("sem_post");

		if (print_log(philo, LOG_SLEEP, get_current_time_in_msec()) < 0)
			break ;
		ft_msleep(philo->time_to_sleep);

		if (print_log(philo, LOG_THINK, get_current_time_in_msec()) < 0)
			break ;
	}
	return (args);
}

void	*monitor_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	printf("Monitor thread created\n");
	while (1)
	{
		if (sem_wait(philo->access_sem) < 0)
			perror("sem_wait");
		if (philo->is_simulation_stop)
		{
			philo->is_philo_success = true;
			if (sem_post(philo->access_sem) < 0)
				perror("sem_post");
			return (args);
		}
		if (philo->time_last_eat != 0 && philo->time_to_die < get_time_diff(philo))
		{
			if (sem_wait(philo->log_sem) < 0)
				perror("sem_wait");
			philo->is_simulation_stop = true;
			philo->is_philo_success = false;
			printf("%lld philo died\n", get_current_time_in_msec());
			if (sem_post(philo->log_sem) < 0)
				perror("sem_post");
			if (sem_post(philo->access_sem) < 0)
				perror("sem_post");
			return (args);
		}
		if (sem_post(philo->access_sem) < 0)
			perror("sem_post");
		ft_usleep(MONITOR_INTERVAL);
	}
	return (args);
}

sem_t	*ft_sem_open(char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, FT_SEM_OFLAG, FT_SEM_MODE, value);
	if (sem == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			printf("Create semaphore %s failed due to EEXIST\n", name);
			sem = sem_open(name, O_RDWR);
			if (sem == SEM_FAILED)
			{
				perror("sem_open");
				return (SEM_FAILED);
			}
			if (sem_close(sem) < 0)
				perror("sem_close");
			if (sem_unlink(name) < 0)
			{
				perror("sem_unlink");
				return (SEM_FAILED);
			}
			sem = sem_open(name, FT_SEM_OFLAG, FT_SEM_MODE, value);
		}
	}
	return (sem);
}

int	create_philo_proc(int time_to_die, int time_to_eat, int time_to_sleep, int num_of_must_eat)
{
	pthread_t	thread_philo;
	pthread_t	thread_monitor;
	t_philo		philo;

	philo.fork_left_sem = ft_sem_open(FT_SEM_FORK, 1);
	if (philo.access_sem == SEM_FAILED)
	{
		perror("sem_open");
		return (EXIT_FAILURE);
	}
	philo.fork_right_sem = ft_sem_open(FT_SEM_FORK, 1);
	if (philo.access_sem == SEM_FAILED)
	{
		perror("sem_open");
		return (EXIT_FAILURE);
	}
	philo.log_sem = ft_sem_open(FT_SEM_LOG, 1);
	if (philo.access_sem == SEM_FAILED)
	{
		perror("sem_open");
		return (EXIT_FAILURE);
	}
	philo.access_sem = ft_sem_open(FT_SEM_NAME, 1);
	if (philo.access_sem == SEM_FAILED)
	{
		perror("sem_open");
		return (EXIT_FAILURE);
	}
	philo.time_to_die = time_to_die;
	philo.time_to_eat = time_to_eat;
	philo.time_to_sleep = time_to_sleep;
	philo.num_of_must_eat = num_of_must_eat;
	philo.num_of_current_eat = 0;
	philo.time_last_eat = 0;
	philo.is_simulation_stop = false;
	philo.is_philo_success = false;

	if (pthread_create(&thread_monitor, NULL, monitor_routine, (void *)&philo) != 0)
		perror("pthread_create");
	if (pthread_create(&thread_philo, NULL, philo_routine, (void *)&philo) != 0)
		perror("pthread_create");
	if (pthread_join(thread_monitor, NULL) != 0)
		perror("pthread_join");
	if (pthread_join(thread_philo, NULL) != 0)
		perror("pthread_join");
	printf("[Result] num of eat %d\n", philo.num_of_current_eat);
	printf("[Monitoring Result] %s\n", philo.is_philo_success ? "success" : "failed");

	if (sem_close(philo.access_sem) < 0)
		perror("sem_close");
	printf("semaphore %s closed\n", FT_SEM_NAME);
	if (sem_unlink(FT_SEM_NAME) < 0)
		perror("sem_unlink");
	printf("semaphore %s unlinked\n", FT_SEM_NAME);
	if (philo.is_philo_success)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	if (argc == 6)
		create_philo_proc(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
	else if (argc == 5)
		create_philo_proc(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), 0);
	else
		printf("check args\n");
}

//int	main(int argc, char **argv)
//{
//	t_args	args;
//
//	validate_arguments(argc);
//	parse_cmdline_arguments(argc, argv, &args);
//	exit(EXIT_SUCCESS);
//}
