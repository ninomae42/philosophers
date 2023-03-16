#include "philosophers.h"

static void	*routine_monitor(void *args);
static bool	is_every_philo_finish_eat(t_info *info);
static bool	is_any_philo_dead(t_info *info);

int	create_and_join_monitor_thread(t_info *info, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, &routine_monitor, (void *)info) != 0)
	{
		ft_puterr(ERR_THREAD_CREATE);
		detach_philo_threads(info, info->num_of_philo);
		destroy_all_mutex(info);
		deallocate_philo_and_fork(info);
		return (1);
	}
	if (pthread_join(*monitor, NULL) != 0)
	{
		ft_puterr(ERR_THREAD_JOIN);
		detach_philo_threads(info, info->num_of_philo);
		destroy_all_mutex(info);
		deallocate_philo_and_fork(info);
		return (1);
	}
	return (0);
}

static void	*routine_monitor(void *args)
{
	t_info	*info;
	bool	need_monitoring;

	info = (t_info *)args;
	need_monitoring = true;
	if (info->num_of_must_eat == 0)
		need_monitoring = false;
	while (1)
	{
		if (need_monitoring && is_every_philo_finish_eat(info))
		{
			pthread_mutex_lock(&info->syslog_mutex);
			info->is_simulation_stop = true;
			pthread_mutex_unlock(&info->syslog_mutex);
			break ;
		}
		if (is_any_philo_dead(info))
			break ;
		ft_msleep(5);
	}
	return (args);
}

static bool	is_every_philo_finish_eat(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < (size_t)info->num_of_philo)
	{
		pthread_mutex_lock(info->philos[i].access_mutex);
		if (info->philos[i].eat_cnt < (size_t)info->num_of_must_eat)
		{
			pthread_mutex_unlock(info->philos[i].access_mutex);
			return (false);
		}
		pthread_mutex_unlock(info->philos[i].access_mutex);
		i++;
	}
	return (true);
}

static bool	is_any_philo_dead(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < (size_t)info->num_of_philo)
	{
		pthread_mutex_lock(info->philos[i].access_mutex);
		if (info->philos[i].last_eat_time != 0
			&& info->time_to_die < get_time_diff(&info->philos[i]))
		{
			pthread_mutex_lock(&info->syslog_mutex);
			printf("%lld %zu died\n", get_current_time_in_msec(), i + 1);
			info->is_simulation_stop = true;
			pthread_mutex_unlock(&info->syslog_mutex);
			pthread_mutex_unlock(info->philos[i].access_mutex);
			return (true);
		}
		pthread_mutex_unlock(info->philos[i].access_mutex);
		i++;
	}
	return (false);
}
