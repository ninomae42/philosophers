#include "philosophers.h"

int	destroy_all_mutexes(t_info *info)
{
	bool	is_err;

	is_err = false;
	if (destroy_philo_mutexes(info->philos, info->num_of_philo) != 0)
		is_err = true;
	if (destroy_fork_mutexes(info->forks, info->num_of_philo) != 0)
		is_err = true;
	if (pthread_mutex_destroy(&(info->syslog_mutex)) != 0)
	{
		ft_puterr(ERR_MTX_DESTROY);
		return (1);
	}
	if (is_err)
		return (1);
	return (0);
}

int	destroy_fork_mutexes(pthread_mutex_t *mutexes, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_destroy(mutexes + i) != 0)
		{
			ft_puterr(ERR_MTX_DESTROY);
			return (1);
		}
		i++;
	}
	return (0);
}

int	destroy_philo_mutexes(t_philo *philos, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_destroy(&(philos[i].access_mutex)) != 0)
		{
			ft_puterr(ERR_MTX_DESTROY);
			return (1);
		}
		i++;
	}
	return (0);
}
