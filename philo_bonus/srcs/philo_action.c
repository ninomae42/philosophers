/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:53:30 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/09 19:53:30 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_wait_forks(t_philo *philo)
{
	if (philo->num_of_must_eat != 0
		&& philo->num_of_must_eat <= philo->num_of_current_eat)
		exit(EXIT_SUCCESS);
	ft_sem_wait(philo->fork_left_sem);
	print_log(philo, LOG_FORK, get_current_time_in_msec());
	ft_sem_wait(philo->fork_right_sem);
	print_log(philo, LOG_FORK, get_current_time_in_msec());
}

void	philo_release_forks(t_philo *philo)
{
	ft_sem_post(philo->fork_right_sem);
	ft_sem_post(philo->fork_left_sem);
}

void	philo_eat(t_philo *philo)
{
	ft_sem_wait(philo->access_sem);
	philo->time_last_eat = get_current_time_in_msec();
	philo->num_of_current_eat++;
	ft_sem_post(philo->access_sem);
	print_log(philo, LOG_EAT, philo->time_last_eat);
	ft_msleep(philo->time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	print_log(philo, LOG_SLEEP, get_current_time_in_msec());
	ft_msleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_log(philo, LOG_THINK, get_current_time_in_msec());
}
