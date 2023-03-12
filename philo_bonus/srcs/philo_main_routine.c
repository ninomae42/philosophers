#include "philo_bonus.h"

void	*routine_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	ft_msleep(philo->start_interval);
	ft_sem_wait(philo->access_sem);
	philo->time_last_eat = get_current_time_in_msec();
	ft_sem_post(philo->access_sem);
	while (1)
	{
		if (philo_wait_forks(philo) < 0)
			break ;
		if (philo_eat(philo) < 0)
			break ;
		philo_release_forks(philo);
		if (philo_sleep(philo) < 0)
			break ;
		if (philo_think(philo) < 0)
			break ;
	}
	return (args);
}

void	*routine_single_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	ft_sem_wait(philo->access_sem);
	philo->time_last_eat = get_current_time_in_msec();
	ft_sem_post(philo->access_sem);
	ft_sem_wait(philo->fork_sem);
	if (print_log(philo, LOG_FORK) < 0)
		return (args);
	ft_sem_post(philo->fork_sem);
	return (args);
}
