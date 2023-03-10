/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_allocate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:53:48 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/10 20:27:12 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static sem_t	**sem_allocate_all_access_sems(size_t num_of_philo)
{
	sem_t	**access_sems;
	size_t	i;

	access_sems = malloc(sizeof(sem_t *) * num_of_philo);
	if (access_sems == NULL)
		ft_puterr_exit(ERR_MEM);
	i = 0;
	while (i < num_of_philo)
	{
		access_sems[i] = sem_create_access(i + 1);
		i++;
	}
	return (access_sems);
}

void	sem_allocate_all_sems(t_sems *sems, int num_of_philo)
{
	size_t	num_half_fork;

	sems->log_sem = sem_create(PHILO_LOG, 1);
	num_half_fork = num_of_philo / 2;
	if (num_of_philo % 2 != 0)
		num_half_fork = num_half_fork + 1;
	sems->pre_fork_sem = sem_create(PHILO_PRE_FORK, num_half_fork);
	sems->fork_sem = sem_create(PHILO_FORK, num_of_philo);
	sems->philo_access_sems = sem_allocate_all_access_sems(num_of_philo);
}

void	sem_deallocate_all_sems(t_sems *sems, size_t num_of_philo)
{
	size_t	i;

	sem_close(sems->log_sem);
	sem_close(sems->fork_sem);
	sem_close(sems->pre_fork_sem);
	i = 0;
	while (i < (size_t)num_of_philo)
	{
		sem_close(sems->philo_access_sems[i]);
		i++;
	}
	free(sems->philo_access_sems);
}
