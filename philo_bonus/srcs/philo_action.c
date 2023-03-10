/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:53:30 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/10 20:00:51 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_wait_forks(t_philo *philo)
{
	if (philo->num_of_must_eat != 0
		&& philo->num_of_must_eat <= philo->num_of_current_eat)
		exit(EXIT_SUCCESS);
	ft_sem_wait(philo->pre_fork_sem);
	ft_sem_wait(philo->fork_sem);
	print_log(philo, LOG_FORK);
	ft_sem_wait(philo->fork_sem);
	print_log(philo, LOG_FORK);
}

void	philo_release_forks(t_philo *philo)
{
	ft_sem_post(philo->fork_sem);
	ft_sem_post(philo->pre_fork_sem);
	ft_sem_post(philo->fork_sem);
}

void	philo_eat(t_philo *philo)
{
	ft_sem_wait(philo->access_sem);
	print_log(philo, LOG_EAT);
	philo->num_of_current_eat++;
	ft_sem_post(philo->access_sem);
	ft_msleep(philo->time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	print_log(philo, LOG_SLEEP);
	ft_msleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_log(philo, LOG_THINK);
}
