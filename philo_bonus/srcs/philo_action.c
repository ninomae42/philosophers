/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:53:30 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/17 00:03:35 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_wait_forks(t_philo *philo)
{
	ft_sem_wait(philo->pre_fork_sem);
	ft_sem_wait(philo->fork_sem);
	if (print_log(philo, LOG_FORK) < 0)
		return (-1);
	ft_sem_wait(philo->fork_sem);
	if (print_log(philo, LOG_FORK) < 0)
		return (-1);
	return (0);
}

void	philo_release_forks(t_philo *philo)
{
	ft_sem_post(philo->fork_sem);
	ft_sem_post(philo->pre_fork_sem);
	ft_sem_post(philo->fork_sem);
}

int	philo_eat(t_philo *philo)
{
	if (print_log(philo, LOG_EAT) < 0)
		return (-1);
	ft_msleep(philo->time_to_eat);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (print_log(philo, LOG_SLEEP) < 0)
		return (-1);
	ft_msleep(philo->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (print_log(philo, LOG_THINK) < 0)
		return (-1);
	ft_msleep(philo->time_to_think);
	return (0);
}
