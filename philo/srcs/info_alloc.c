/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:25:27 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/16 23:25:27 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	allocate_philo_and_fork(t_info *info)
{
	bool	is_err;

	is_err = false;
	info->philos = (t_philo *)ft_malloc(sizeof(t_philo) * info->num_of_philo);
	if (info->philos == NULL)
		is_err = true;
	info->forks = (pthread_mutex_t *)ft_malloc(
			sizeof(pthread_mutex_t) * info->num_of_philo);
	if (info->forks == NULL)
		is_err = true;
	info->access_mutexes = (pthread_mutex_t *)ft_malloc(
			sizeof(pthread_mutex_t) * info->num_of_philo);
	if (info->access_mutexes == NULL)
		is_err = true;
	if (is_err)
	{
		deallocate_philo_and_fork(info);
		return (1);
	}
	info->is_simulation_stop = false;
	return (0);
}

void	deallocate_philo_and_fork(t_info *info)
{
	free(info->philos);
	free(info->forks);
	free(info->access_mutexes);
}
