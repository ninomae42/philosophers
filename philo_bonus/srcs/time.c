/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:54:01 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/09 19:54:02 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_time	get_current_time_in_usec(void)
{
	t_time			current_in_usec;
	struct timeval	current;

	if (gettimeofday(&current, NULL) != 0)
		ft_puterr(ERR_GET_TIME);
	current_in_usec = current.tv_sec * SEC_TO_MSEC * MSEC_TO_USEC
		+ current.tv_usec;
	return (current_in_usec);
}

t_time	get_current_time_in_msec(void)
{
	t_time			current_in_msec;
	struct timeval	current;

	if (gettimeofday(&current, NULL) != 0)
		ft_puterr(ERR_GET_TIME);
	current_in_msec = current.tv_sec * SEC_TO_MSEC
		+ current.tv_usec / USEC_TO_MSEC;
	return (current_in_msec);
}

void	ft_usleep(unsigned int usec)
{
	t_time	end_time;
	t_time	left_time_to_sleep;

	end_time = get_current_time_in_usec() + usec;
	while (1)
	{
		left_time_to_sleep = end_time - get_current_time_in_usec();
		if (left_time_to_sleep <= 0)
			break ;
		usleep(left_time_to_sleep / 2);
	}
}

void	ft_msleep(unsigned int msec)
{
	t_time	end_time;
	t_time	left_time_to_sleep;

	end_time = get_current_time_in_usec() + (msec * MSEC_TO_USEC);
	while (1)
	{
		left_time_to_sleep = end_time - get_current_time_in_usec();
		if (left_time_to_sleep <= 0)
			break ;
		usleep(left_time_to_sleep / 2);
	}
}

t_time	get_time_diff(t_philo *philo)
{
	t_time	diff;

	diff = get_current_time_in_msec() - philo->time_last_eat;
	return (diff);
}
