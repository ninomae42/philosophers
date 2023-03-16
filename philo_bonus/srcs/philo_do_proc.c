/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:53:39 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/17 00:20:49 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_set_infos(t_philo *philo,
				size_t index, t_args *arg, t_sems *sem);
static void	create_philo_thread(
				t_philo *philo, pthread_t *thread, size_t num_philo);

void	do_philo_proc(size_t index, t_args *arg, t_sems *sem)
{
	t_philo		philo;
	pthread_t	thread_philo;
	pthread_t	thread_monitor;

	philo_set_infos(&philo, index, arg, sem);
	if (pthread_create(&thread_monitor, NULL, routine_monitor, &philo) != 0)
		ft_puterr_exit(ERR_THREAD_CREATE);
	create_philo_thread(&philo, &thread_philo, arg->num_of_philo);
	if (pthread_join(thread_monitor, NULL) != 0)
		ft_puterr_exit(ERR_THREAD_JOIN);
	if (pthread_join(thread_philo, NULL) != 0)
		ft_puterr_exit(ERR_THREAD_JOIN);
	sem_deallocate_all_sems(sem, arg->num_of_philo);
	if (!philo.is_simulation_success)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static void	create_philo_thread(
			t_philo *philo, pthread_t *thread, size_t num_philo)
{
	if (num_philo == 1)
	{
		if (pthread_create(thread, NULL, routine_single_philo, philo) != 0)
			ft_puterr_exit(ERR_THREAD_CREATE);
	}
	else
	{
		if (pthread_create(thread, NULL, routine_philo, philo) != 0)
			ft_puterr_exit(ERR_THREAD_CREATE);
	}
}

static void	set_interval(t_philo *philo)
{
	t_time	total_interval;
	t_time	eat_interval;
	size_t	num_of_fork_sets;

	philo->start_interval = 0;
	if (philo->num_of_philo % 2 == 0)
		return ;
	num_of_fork_sets = philo->num_of_philo / 2;
	if (num_of_fork_sets == 0)
		return ;
	eat_interval = philo->time_to_eat / num_of_fork_sets;
	total_interval = 0;
	if (1 < philo->philo_index)
		total_interval = eat_interval * (philo->philo_index / 2);
	if (philo->philo_index % 2 == 0)
		total_interval += philo->time_to_eat;
	philo->start_interval = total_interval;
}

static void	set_time_to_think(t_philo *philo)
{
	t_time	time_to_think;
	t_time	eat_interval;
	size_t	num_of_fork_sets;

	philo->time_to_think = 0;
	if (philo->num_of_philo % 2 == 0)
		return ;
	num_of_fork_sets = philo->num_of_philo / 2;
	if (num_of_fork_sets == 0)
		return ;
	eat_interval = philo->time_to_eat / num_of_fork_sets;
	time_to_think = eat_interval * philo->num_of_philo
		- philo->time_to_eat - philo->time_to_sleep;
	if (0 < time_to_think)
		philo->time_to_think = time_to_think;
}

static void	philo_set_infos(
			t_philo *philo, size_t index, t_args *arg, t_sems *sem)
{
	philo->num_of_philo = arg->num_of_philo;
	philo->time_to_die = arg->time_to_die;
	philo->time_to_eat = arg->time_to_eat;
	philo->time_to_sleep = arg->time_to_sleep;
	philo->num_of_must_eat = arg->num_of_must_eat;
	philo->log_sem = sem->log_sem;
	philo->fork_sem = sem->fork_sem;
	philo->pre_fork_sem = sem->pre_fork_sem;
	philo->access_sem = sem->philo_access_sems[index - 1];
	philo->philo_index = index;
	philo->time_last_eat = 0;
	philo->num_of_current_eat = 0;
	philo->is_simulation_stop = false;
	philo->is_simulation_success = false;
	set_interval(philo);
	set_time_to_think(philo);
}
