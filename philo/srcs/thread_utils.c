/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:56:00 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/10 19:32:46 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	detach_all_threads(t_info *info, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_detach(info->philos[i].thread) != 0)
		{
			ft_puterr(ERR_THREAD_DETATCH);
			return (1);
		}
		i++;
	}
	return (0);
}

int	print_philo_log(t_philo *philo, int log_type)
{
	pthread_mutex_lock(philo->syslog_mutex);
	if (philo->info->is_simulation_stop)
	{
		pthread_mutex_unlock(philo->syslog_mutex);
		return (1);
	}
	if (log_type == LOG_FORK)
		printf("%lld %d has taken a fork\n",
			get_current_time_in_msec(), philo->id);
	else if (log_type == LOG_SLEEP)
		printf("%lld %d is sleeping\n",
			get_current_time_in_msec(), philo->id);
	else if (log_type == LOG_THINK)
		printf("%lld %d is thinking\n",
			get_current_time_in_msec(), philo->id);
	else if (log_type == LOG_EAT)
	{
		philo->last_eat_time = get_current_time_in_msec();
		printf("%lld %d is eating\n",
			philo->last_eat_time, philo->id);
	}
	pthread_mutex_unlock(philo->syslog_mutex);
	return (0);
}
