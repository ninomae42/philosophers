/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:26:03 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/16 23:26:04 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	create_philo_single_thread(t_info *info);

int	create_philo_thread(t_info *info)
{
	size_t	i;

	i = 0;
	if (info->num_of_philo == 1)
		return (create_philo_single_thread(info));
	while (i < (size_t)info->num_of_philo)
	{
		if (pthread_create(&(info->philos[i].thread), NULL,
				&routine_philo, &(info->philos[i])) != 0)
		{
			ft_puterr(ERR_THREAD_CREATE);
			detach_philo_threads(info, i);
			destroy_all_mutex(info);
			deallocate_philo_and_fork(info);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	create_philo_single_thread(t_info *info)
{
	if (pthread_create(&(info->philos[0].thread), NULL,
			&routine_single_philo, &(info->philos[0])) != 0)
	{
		ft_puterr(ERR_THREAD_CREATE);
		if (pthread_detach(info->philos[0].thread) != 0)
			ft_puterr(ERR_THREAD_DETATCH);
		destroy_all_mutex(info);
		deallocate_philo_and_fork(info);
		return (1);
	}
	return (0);
}

int	join_philo_threads(t_info *info)
{
	size_t	i;
	bool	is_err;

	i = 0;
	is_err = false;
	while (i < (size_t)info->num_of_philo)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
			is_err = true;
		i++;
	}
	if (is_err)
	{
		ft_puterr(ERR_THREAD_JOIN);
		destroy_all_mutex(info);
		deallocate_philo_and_fork(info);
		return (1);
	}
	return (0);
}

void	detach_philo_threads(t_info *info, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_detach(info->philos[i].thread) != 0)
			ft_puterr(ERR_THREAD_DETATCH);
		i++;
	}
}
