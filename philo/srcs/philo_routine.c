/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:25:54 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/16 23:25:55 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death_release_fork(t_philo *philo);

void	*routine_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	ft_msleep(philo->start_interval);
	pthread_mutex_lock(philo->access_mutex);
	philo->last_eat_time = get_current_time_in_msec();
	pthread_mutex_unlock(philo->access_mutex);
	while (1)
	{
		if (philo_wait_forks(philo) != 0)
			break ;
		if (philo_eat(philo) != 0)
			break ;
		philo_release_forks(philo);
		if (philo_sleep(philo) != 0)
			break ;
		if (philo_think(philo) != 0)
			break ;
	}
	return (args);
}

void	*routine_single_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(philo->access_mutex);
	philo->last_eat_time = get_current_time_in_msec();
	pthread_mutex_unlock(philo->access_mutex);
	while (1)
	{
		pthread_mutex_lock(philo->fork_right);
		if (print_philo_log(philo, LOG_FORK) != 0)
		{
			pthread_mutex_unlock(philo->fork_right);
			break ;
		}
		ft_msleep(philo->time_to_die * 2);
		if (check_death_release_fork(philo) != 0)
			break ;
	}
	return (args);
}

static int	check_death_release_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->syslog_mutex);
	if (philo->info->is_simulation_stop)
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->syslog_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->syslog_mutex);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}
