#include "philo_bonus.h"

static void	philo_set_infos(t_philo *philo, size_t index, t_args *arg, t_sems *sem);
static void	*routine_philo(void *args);
static void	*routine_monitor(void *args);

void	do_philo_proc(size_t index, t_args *arg, t_sems *sem)
{
	t_philo		philo;
	pthread_t	thread_philo;
	pthread_t	thread_monitor;

	philo_set_infos(&philo, index, arg, sem);
	if (pthread_create(&thread_monitor, NULL, routine_monitor, &philo) != 0)
		ft_puterr_exit(ERR_THREAD_CREATE);
	if (pthread_create(&thread_philo, NULL, routine_philo, &philo) != 0)
		ft_puterr_exit(ERR_THREAD_CREATE);
	if (pthread_join(thread_monitor, NULL) != 0)
		ft_puterr_exit(ERR_THREAD_JOIN);
	if (pthread_join(thread_philo, NULL) != 0)
		ft_puterr_exit(ERR_THREAD_JOIN);
	exit(EXIT_SUCCESS);
}

static void	*routine_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	printf("Philo %zu craeted\n", philo->philo_index);
	ft_sem_wait(philo->access_sem);
	philo->time_last_eat = get_current_time_in_msec();
	ft_sem_post(philo->access_sem);
	while (1)
	{
		philo_wait_forks(philo);
		philo_eat(philo);
		philo_release_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (args);
}

static void	*routine_monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	printf("Monitor %zu craeted\n", philo->philo_index);
	while (1)
	{
		ft_sem_wait(philo->access_sem);
		if (philo->time_last_eat != 0 && philo->time_to_die < get_time_diff(philo))
		{
			print_log(philo, LOG_DIE, get_current_time_in_msec());
			ft_sem_post(philo->access_sem);
			exit(EXIT_FAILURE);
		}
		ft_sem_post(philo->access_sem);
		ft_usleep(MONITOR_INTERVAL);
	}
	return (args);
}


static void	philo_set_infos(t_philo *philo, size_t index, t_args *arg, t_sems *sem)
{
	philo->time_to_die = arg->time_to_die;
	philo->time_to_eat = arg->time_to_eat;
	philo->time_to_sleep = arg->time_to_sleep;
	philo->num_of_must_eat = arg->num_of_must_eat;
	philo->log_sem = sem->log_sem;
	philo->fork_left_sem = sem->fork_left_sem;
	philo->fork_right_sem = sem->fork_right_sem;
	philo->access_sem = sem->philo_access_sems[index - 1];
	philo->philo_index = index;
	philo->time_last_eat = 0;
	philo->num_of_current_eat = 0;
}