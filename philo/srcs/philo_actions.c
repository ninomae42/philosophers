/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:55:43 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/13 02:38:17 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->access_mutex));
	if (print_philo_log(philo, LOG_EAT) != 0)
	{
		if (pthread_mutex_unlock(&(philo->access_mutex)) != 0)
			return (1);
		if (pthread_mutex_unlock(philo->right_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(philo->left_fork) != 0)
			return (1);
		return (1);
	}
	philo->eat_cnt++;
	pthread_mutex_unlock(&(philo->access_mutex));
	ft_msleep(philo->info->time_to_eat);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (print_philo_log(philo, LOG_SLEEP) != 0)
		return (1);
	ft_msleep(philo->info->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (print_philo_log(philo, LOG_THINK) != 0)
		return (1);
	return (0);
}
