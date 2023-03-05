#include "philo_bonus.h"

# define FT_SEM_OFLAG (O_CREAT | O_EXCL)
# define FT_SEM_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
# define MAX_RES 2000000
# define FT_SEM_NAME "/semtest"

int		result = 0;
sem_t	*global_sem;

void	*thread_routine(void *args)
{
	int	tmp;

	printf("Thread craeted\n");
	while (1)
	{
		if (sem_wait(global_sem) < 0)
			perror("sem_wait");
		if (MAX_RES <= result)
		{
			if (sem_post(global_sem) < 0)
				perror("sem_post1");
			break ;
		}
		tmp = result;
		tmp++;
		result = tmp;
		if (sem_post(global_sem) < 0)
			perror("sem_post2");
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

void	sem_playground(char *name)
{
	pthread_t	thread_main;
	pthread_t	thread_monitor;

	global_sem = ft_sem_open(name, 1);
	if (global_sem == SEM_FAILED)
	{
		perror("sem_open");
		return ;
	}
	printf("semaphore %s created\n", name);

	if (pthread_create(&thread_main, NULL, thread_routine, NULL) != 0)
		perror("pthread_create");
	if (pthread_create(&thread_monitor, NULL, thread_routine, NULL) != 0)
		perror("pthread_create");
	if (pthread_join(thread_main, NULL) != 0)
		perror("pthread_join");
	if (pthread_join(thread_monitor, NULL) != 0)
		perror("pthread_join");
	printf("[LOG]result %d\n", result);

	if (sem_close(global_sem) < 0)
		perror("sem_close");
	printf("semaphore %s closed\n", name);
	if (sem_unlink(name) < 0)
		perror("sem_unlink");
	printf("semaphore %s unlinked\n", name);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	
	sem_playground(FT_SEM_NAME);

}

//int	main(int argc, char **argv)
//{
//	t_args	args;
//
//	validate_arguments(argc);
//	parse_cmdline_arguments(argc, argv, &args);
//	exit(EXIT_SUCCESS);
//}
