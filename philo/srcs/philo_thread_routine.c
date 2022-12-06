#include "philosophers.h"

static int	set_initial_state(t_philo *philo);
static int	check_death_release_fork(t_philo *philo);

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(300);
	if (set_initial_state(philo) != 0)
		return (arg);
	while (1)
	{
		if (philo_take_two_forks(philo) != 0)
			return (arg);
		if (philo_eat(philo) != 0)
			return (arg);
		if (philo_release_two_forks(philo) != 0)
			return (arg);
		if (philo_sleep(philo) != 0)
			return (arg);
		if (philo_think(philo) != 0)
			return (arg);
	}
	return (arg);
}

void	*routine_single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (set_initial_state(philo) != 0)
		return (arg);
	while (1)
	{
		if (take_left_fork(philo) != 0)
			return (arg);
		ft_msleep(philo->info->time_to_die * 2);
		if (check_death_release_fork(philo) != 0)
			return (arg);
	}
	return (arg);
}

static int	set_initial_state(t_philo *philo)
{
	if (pthread_mutex_lock(&(philo->access_mutex)) != 0)
		return (1);
	philo->last_eat_time_in_usec = get_current_time_in_usec();
	philo->status = STATUS_RUNNING;
	if (pthread_mutex_unlock(&(philo->access_mutex)) != 0)
		return (1);
	return (0);
}

static int	check_death_release_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->syslog_mutex) != 0)
		return (1);
	if (philo->info->is_simulation_stop)
	{
		if (pthread_mutex_unlock(philo->left_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(philo->syslog_mutex) != 0)
			return (1);
		return (1);
	}
	if (pthread_mutex_unlock(philo->left_fork) != 0)
		return (1);
	if (pthread_mutex_unlock(philo->syslog_mutex) != 0)
		return (1);
	return (0);
}
