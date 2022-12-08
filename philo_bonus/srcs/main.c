#include "philosophers.h"

t_info	*init_global_info(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL)
		return (NULL);
	if (validate_argument_count(argc) != 0)
	{
		free(info);
		return (NULL);
	}
	if (set_cmdline_arguments(argc, argv, info) != 0)
	{
		free(info);
		return (NULL);
	}
	if (is_each_cmdline_arguments_valid(info) != 0)
	{
		free(info);
		return (NULL);
	}
	return (info);
}

int	init_named_semaphore(t_info *info)
{
	info->forks = sem_open(
		SEM_FORK_NAME, SEM_OFLAG, SEM_MODE, info->num_of_philo);
	if (info->forks == SEM_FAILED)
	{
		free(info);
		return (1);
	}
	info->sys_log = sem_open(
		SEM_SYSLOG_NAME, SEM_OFLAG, SEM_MODE, 1);
	if (info->sys_log == SEM_FAILED)
	{
		sem_close(info->forks);
		sem_unlink(SEM_FORK_NAME);
		free(info);
		return (1);
	}
	return (0);
}

void	unlink_all_semaphore(t_info *info)
{
	if (sem_close(info->forks) != 0)
		perror("Unable to close semaphore");
	if (sem_unlink(SEM_FORK_NAME) != 0)
		perror("Unable to unlink semaphore");
	if (sem_close(info->sys_log) != 0)
		perror("Unable to close semaphore");
	if (sem_unlink(SEM_SYSLOG_NAME) != 0)
		perror("Unable to unlink semaphore");
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = init_global_info(argc, argv);
	if (info == NULL)
		exit(EXIT_FAILURE);
	printf("num_philo: %d\n", info->num_of_philo);
	printf("time_to_die: %d\n", info->time_to_die);
	printf("time_to_eat: %d\n", info->time_to_eat);
	printf("time_to_sleep: %d\n", info->time_to_sleep);
	printf("min_eat_cnt: %d\n", info->num_of_times_must_eat);
	if (init_named_semaphore(info) != 0)
		exit(EXIT_FAILURE);

	unlink_all_semaphore(info);
	free(info);
	exit(EXIT_SUCCESS);
}
