/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:55:31 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/10 19:26:25 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_any_philo_dead(t_info *info);
static bool	is_every_philo_finish_eat(t_info *info);

void	*routine_monitor(void *arg)
{
	t_info	*info;
	bool	need_monitoring_eat;

	info = (t_info *)arg;
	need_monitoring_eat = true;
	if (info->num_of_times_each_philo_must_eat == 0)
		need_monitoring_eat = false;
	while (1)
	{
		if (need_monitoring_eat && is_every_philo_finish_eat(info))
		{
			pthread_mutex_lock(&(info->syslog_mutex));
			info->is_simulation_stop = true;
			pthread_mutex_unlock(&(info->syslog_mutex));
			return (arg);
		}
		if (is_any_philo_dead(info))
			return (arg);
		ft_msleep(5);
	}
	return (arg);
}

int	create_join_monitor_thread(t_info *info, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, &routine_monitor, (void *)info) != 0)
	{
		detach_all_threads(info, info->num_of_philo);
		destroy_all_mutexes(info);
		free_global_info(info);
		return (1);
	}
	if (pthread_join(*monitor, NULL) != 0)
	{
		destroy_all_mutexes(info);
		free_global_info(info);
		return (1);
	}
	return (0);
}

static bool	is_every_philo_finish_eat(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < (size_t)info->num_of_philo)
	{
		pthread_mutex_lock(&(info->philos[i].access_mutex));
		if (info->philos[i].eat_cnt
			< (size_t)info->num_of_times_each_philo_must_eat)
		{
			pthread_mutex_unlock(&(info->philos[i].access_mutex));
			return (false);
		}
		pthread_mutex_unlock(&(info->philos[i].access_mutex));
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
		pthread_mutex_lock(&(info->philos[i].access_mutex));
		if (info->philos[i].status == STATUS_RUNNING)
		{
			if (info->time_to_die < get_time_difference(&(info->philos[i])))
			{
				pthread_mutex_lock(&(info->syslog_mutex));
				printf("%lld %zu died\n", get_current_time_in_msec(), i + 1);
				info->is_simulation_stop = true;
				pthread_mutex_unlock(&(info->syslog_mutex));
				pthread_mutex_unlock(&(info->philos[i].access_mutex));
				return (true);
			}
		}
		pthread_mutex_unlock(&(info->philos[i].access_mutex));
		i++;
	}
	return (false);
}
