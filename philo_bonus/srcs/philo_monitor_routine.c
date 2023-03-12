/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor_routine.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 00:51:21 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/13 00:51:22 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	is_philo_finish_eat(t_philo *philo);
static bool	is_philo_die(t_philo *philo);

void	*routine_monitor(void *args)
{
	t_philo	*philo;
	bool	need_monitoring;

	philo = (t_philo *)args;
	need_monitoring = true;
	if (philo->num_of_must_eat == 0)
		need_monitoring = false;
	while (1)
	{
		if (need_monitoring && is_philo_finish_eat(philo))
			break ;
		if (is_philo_die(philo))
			break ;
		ft_msleep(MONITOR_INTERVAL);
	}
	return (args);
}

static bool	is_philo_finish_eat(t_philo *philo)
{
	ft_sem_wait(philo->access_sem);
	if (philo->num_of_must_eat <= philo->num_of_current_eat)
	{
		philo->is_simulation_stop = true;
		philo->is_simulation_success = true;
		ft_sem_post(philo->access_sem);
		return (true);
	}
	ft_sem_post(philo->access_sem);
	return (false);
}

static bool	is_philo_die(t_philo *philo)
{
	ft_sem_wait(philo->access_sem);
	if (philo->time_last_eat != 0
		&& philo->time_to_die < get_time_diff(philo))
	{
		philo->is_simulation_stop = true;
		philo->is_simulation_success = false;
		ft_sem_wait(philo->log_sem);
		printf("%lld %zu died\n",
			get_current_time_in_msec(), philo->philo_index);
		ft_sem_post(philo->access_sem);
		return (true);
	}
	ft_sem_post(philo->access_sem);
	return (false);
}
