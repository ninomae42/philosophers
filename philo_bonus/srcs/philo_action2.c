/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:53:34 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/22 16:25:07 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_log(t_philo *philo, t_log_type log_type)
{
	ft_sem_wait(philo->access_sem);
	if (philo->is_simulation_stop)
		return (-1);
	ft_sem_wait(philo->log_sem);
	if (log_type == LOG_FORK)
		printf("%lld %zu has taken a fork\n",
			get_current_time_in_msec(), philo->philo_index);
	else if (log_type == LOG_SLEEP)
		printf("%lld %zu is sleeping\n",
			get_current_time_in_msec(), philo->philo_index);
	else if (log_type == LOG_THINK)
		printf("%lld %zu is thinking\n",
			get_current_time_in_msec(), philo->philo_index);
	else if (log_type == LOG_EAT)
	{
		philo->time_last_eat = get_current_time_in_msec();
		philo->num_of_current_eat++;
		printf("%lld %zu is eating\n",
			philo->time_last_eat, philo->philo_index);
	}
	ft_sem_post(philo->log_sem);
	ft_sem_post(philo->access_sem);
	return (0);
}

bool	philo_is_philo_dead(t_philo *philo)
{
	ft_sem_wait(philo->access_sem);
	if (philo->time_to_die < get_time_diff(philo))
	{
		if (!philo->is_simulation_stop)
		{
			philo->is_simulation_stop = true;
			philo->is_simulation_success = false;
			ft_sem_wait(philo->log_sem);
			printf("%lld %zu died\n",
				get_current_time_in_msec(), philo->philo_index);
		}
		ft_sem_post(philo->access_sem);
		return (true);
	}
	ft_sem_post(philo->access_sem);
	return (false);
}
