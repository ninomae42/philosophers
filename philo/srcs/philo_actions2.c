/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:55:47 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/09 19:55:48 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_left_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (1);
	if (print_philo_log(philo, LOG_FORK, 0) != 0)
	{
		if (pthread_mutex_unlock(philo->left_fork) != 0)
			return (1);
		return (1);
	}
	return (0);
}

int	take_right_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (1);
	if (print_philo_log(philo, LOG_FORK, 0) != 0)
	{
		if (pthread_mutex_unlock(philo->right_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(philo->left_fork) != 0)
			return (1);
		return (1);
	}
	return (0);
}

int	philo_take_two_forks(t_philo *philo)
{
	if (take_left_fork(philo) != 0)
		return (1);
	if (take_right_fork(philo) != 0)
		return (1);
	return (0);
}

int	philo_release_two_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		return (1);
	if (pthread_mutex_unlock(philo->left_fork) != 0)
		return (1);
	return (0);
}
