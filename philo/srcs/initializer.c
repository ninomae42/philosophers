/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:55:24 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/10 19:15:12 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_global_info	*init_global_info(int argc, char **argv)
{
	t_global_info	*info;

	if (validate_argument_count(argc) != 0)
		return (NULL);
	info = (t_global_info *)malloc(sizeof(t_global_info));
	if (info == NULL)
	{
		ft_puterr(ERR_MEM);
		return (NULL);
	}
	if (set_cmdline_arguments(argc, argv, info) != 0)
	{
		ft_puterr(ERR_ARGS);
		free(info);
		return (NULL);
	}
	if (is_each_cmdline_arguments_valid(info) != 0)
	{
		free(info);
		return (NULL);
	}
	info->is_simulation_stop = false;
	return (info);
}

int	allocate_philo_and_fork(t_info *info)
{
	info->philos = (t_philo *)malloc(sizeof(t_philo) * (info->num_of_philo));
	if (info->philos == NULL)
	{
		ft_puterr(ERR_MEM);
		return (1);
	}
	info->forks = (t_fork *)malloc(sizeof(t_fork) * (info->num_of_philo));
	if (info->forks == NULL)
	{
		ft_puterr(ERR_MEM);
		free(info->philos);
		free(info);
		return (1);
	}
	return (0);
}

void	free_global_info(t_info *info)
{
	free(info->philos);
	free(info->forks);
	free(info);
}

void	set_fork_mutex(t_info *info, size_t i)
{
	if (i == (size_t)(info->num_of_philo - 1))
	{
		info->philos[i].left_fork = &(info->forks[i]);
		info->philos[i].right_fork = &(info->forks[0]);
	}
	else
	{
		info->philos[i].left_fork = &(info->forks[i]);
		info->philos[i].right_fork = &(info->forks[i + 1]);
	}
}

void	init_philos(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < (size_t)info->num_of_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].eat_cnt = 0;
		info->philos[i].last_eat_time = 0;
		info->philos[i].syslog_mutex = &(info->syslog_mutex);
		info->philos[i].info = info;
		info->philos[i].status = STATUS_INIT;
		set_fork_mutex(info, i);
		i++;
	}
}
