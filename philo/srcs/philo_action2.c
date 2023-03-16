/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:25:46 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/16 23:25:47 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_philo_log(t_philo *philo, t_log_type log_type)
{
	pthread_mutex_lock(philo->syslog_mutex);
	if (philo->info->is_simulation_stop)
	{
		pthread_mutex_unlock(philo->syslog_mutex);
		return (1);
	}
	if (log_type == LOG_FORK)
		printf("%lld %zu has taken a fork\n",
			get_current_time_in_msec(), philo->id);
	else if (log_type == LOG_SLEEP)
		printf("%lld %zu is sleeping\n",
			get_current_time_in_msec(), philo->id);
	else if (log_type == LOG_THINK)
		printf("%lld %zu is thinking\n",
			get_current_time_in_msec(), philo->id);
	else if (log_type == LOG_EAT)
	{
		philo->last_eat_time = get_current_time_in_msec();
		printf("%lld %zu is eating\n",
			philo->last_eat_time, philo->id);
	}
	pthread_mutex_unlock(philo->syslog_mutex);
	return (0);
}
