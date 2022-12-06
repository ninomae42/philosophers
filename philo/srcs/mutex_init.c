#include "philosophers.h"

static int	init_sys_mutex(t_info *info);
static int	init_fork_mutexes(t_info *info);
static int	init_philo_mutexes(t_info *info);

int	init_all_mutexes(t_info *info)
{
	if (init_sys_mutex(info) != 0)
	{
		free_global_info(info);
		return (1);
	}
	if (init_fork_mutexes(info) != 0)
	{
		if (pthread_mutex_destroy(&(info->syslog_mutex)) != 0)
			ft_puterr(ERR_MTX_DESTROY);
		free_global_info(info);
		return (1);
	}
	if (init_philo_mutexes(info) != 0)
	{
		if (pthread_mutex_destroy(&(info->syslog_mutex)) != 0)
			ft_puterr(ERR_MTX_DESTROY);
		destroy_fork_mutexes(info->forks, info->num_of_philo);
		free_global_info(info);
		return (1);
	}
	return (0);
}

static int	init_sys_mutex(t_info *info)
{
	if (pthread_mutex_init(&(info->syslog_mutex), NULL) != 0)
	{
		ft_puterr(ERR_MTX_INIT);
		return (1);
	}
	return (0);
}

static int	init_fork_mutexes(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < (size_t)info->num_of_philo)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL) != 0)
			break ;
		i++;
	}
	if (i != (size_t)info->num_of_philo)
	{
		ft_puterr(ERR_MTX_INIT);
		destroy_fork_mutexes(info->forks, i);
		return (1);
	}
	return (0);
}

static int	init_philo_mutexes(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < (size_t)info->num_of_philo)
	{
		if (pthread_mutex_init(&(info->philos[i].access_mutex), NULL) != 0)
			break ;
		i++;
	}
	if (i != (size_t)info->num_of_philo)
	{
		ft_puterr(ERR_MTX_INIT);
		destroy_philo_mutexes(info->philos, i);
		return (1);
	}
	return (0);
}
