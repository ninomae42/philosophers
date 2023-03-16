/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:25:59 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/16 23:26:00 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_fork_mutex(t_info *info, size_t i)
{
	if (i == (size_t)info->num_of_philo - 1)
	{
		info->philos[i].fork_left = &(info->forks[0]);
		info->philos[i].fork_right = &(info->forks[i]);
	}
	else
	{
		info->philos[i].fork_left = &(info->forks[i]);
		info->philos[i].fork_right = &(info->forks[i + 1]);
	}
}

void	set_interval(t_info *info, size_t i)
{
	t_time	total_interval;
	t_time	eat_interval;
	size_t	num_of_fork_sets;

	info->philos[i].start_interval = 0;
	if (info->num_of_philo % 2 == 0)
	{
		if (info->philos[i].id % 2 == 0)
			info->philos[i].start_interval = info->time_to_eat;
		return ;
	}
	num_of_fork_sets = info->num_of_philo / 2;
	eat_interval = info->time_to_eat / num_of_fork_sets;
	total_interval = 0;
	if (1 < info->philos[i].id)
		total_interval = eat_interval * (info->philos[i].id / 2);
	if (info->philos[i].id % 2 == 0)
		total_interval += info->time_to_eat;
	info->philos[i].start_interval = total_interval;
}

void	set_time_to_think(t_info *info, size_t i)
{
	t_time	time_to_think;
	t_time	eat_interval;
	size_t	num_of_fork_sets;

	info->philos[i].time_to_think = 0;
	if (info->num_of_philo % 2 == 0)
		return ;
	num_of_fork_sets = info->num_of_philo / 2;
	eat_interval = info->time_to_eat / num_of_fork_sets;
	time_to_think = eat_interval * info->num_of_philo
		- info->time_to_eat - info->time_to_sleep;
	if (0 < time_to_think)
		info->philos[i].time_to_think = time_to_think;
}

void	set_philo_info(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < (size_t)info->num_of_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].time_to_die = info->time_to_die;
		info->philos[i].time_to_eat = info->time_to_eat;
		info->philos[i].time_to_sleep = info->time_to_sleep;
		info->philos[i].num_of_must_eat = info->num_of_must_eat;
		info->philos[i].eat_cnt = 0;
		info->philos[i].last_eat_time = 0;
		info->philos[i].syslog_mutex = &(info->syslog_mutex);
		info->philos[i].access_mutex = &(info->access_mutexes[i]);
		info->philos[i].info = info;
		set_fork_mutex(info, i);
		set_interval(info, i);
		set_time_to_think(info, i);
		i++;
	}
}
