/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:25:42 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/16 23:25:42 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_wait_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (print_philo_log(philo, LOG_FORK) != 0)
	{
		pthread_mutex_unlock(philo->fork_left);
		return (1);
	}
	pthread_mutex_lock(philo->fork_right);
	if (print_philo_log(philo, LOG_FORK) != 0)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	return (0);
}

void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->access_mutex);
	if (print_philo_log(philo, LOG_EAT) != 0)
	{
		pthread_mutex_unlock(philo->access_mutex);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return (1);
	}
	philo->eat_cnt++;
	pthread_mutex_unlock(philo->access_mutex);
	ft_msleep(philo->time_to_eat);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (print_philo_log(philo, LOG_SLEEP))
		return (1);
	ft_msleep(philo->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (print_philo_log(philo, LOG_THINK))
		return (1);
	ft_msleep(philo->time_to_think);
	return (0);
}
