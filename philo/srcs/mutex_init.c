#include "philosophers.h"

static int	ft_mutex_init(pthread_mutex_t *mutex);
static int	init_mutexes(pthread_mutex_t *mutex, size_t num);
static void	destroy_mutexes(pthread_mutex_t *mutex, size_t num);

int	init_all_mutex(t_info *info)
{
	if (ft_mutex_init(&(info->syslog_mutex)) != 0)
	{
		deallocate_philo_and_fork(info);
		return (1);
	}
	if (init_mutexes(info->forks, info->num_of_philo) != 0)
	{
		if (pthread_mutex_destroy(&(info->syslog_mutex)) != 0)
			ft_puterr(ERR_MTX_DESTROY);
		deallocate_philo_and_fork(info);
		return (1);
	}
	if (init_mutexes(info->access_mutexes, info->num_of_philo) != 0)
	{
		if (pthread_mutex_destroy(&(info->syslog_mutex)) != 0)
			ft_puterr(ERR_MTX_DESTROY);
		destroy_mutexes(info->forks, info->num_of_philo);
		deallocate_philo_and_fork(info);
		return (1);
	}
	return (0);
}

void	destroy_all_mutex(t_info *info)
{
	if (pthread_mutex_destroy(&(info->syslog_mutex)) != 0)
		ft_puterr(ERR_MTX_DESTROY);
	destroy_mutexes(info->access_mutexes, info->num_of_philo);
	destroy_mutexes(info->forks, info->num_of_philo);
}

static int	ft_mutex_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		ft_puterr(ERR_MTX_INIT);
		return (1);
	}
	return (0);
}

static int	init_mutexes(pthread_mutex_t *mutex, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if (ft_mutex_init(&mutex[i]) != 0)
		{
			destroy_mutexes(mutex, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	destroy_mutexes(pthread_mutex_t *mutex, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if (pthread_mutex_destroy(mutex + i) != 0)
			ft_puterr(ERR_MTX_DESTROY);
		i++;
	}
}
