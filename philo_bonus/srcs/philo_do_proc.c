/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do_proc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:53:39 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/10 20:20:15 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_set_infos(t_philo *philo,
				size_t index, t_args *arg, t_sems *sem);
static void	*routine_philo(void *args);
static void	*routine_monitor(void *args);

void	do_philo_proc(size_t index, t_args *arg, t_sems *sem)
{
	t_philo		philo;
	pthread_t	thread_philo;
	pthread_t	thread_monitor;

	philo_set_infos(&philo, index, arg, sem);
	if (pthread_create(&thread_monitor, NULL, routine_monitor, &philo) != 0)
		ft_puterr_exit(ERR_THREAD_CREATE);
	if (pthread_create(&thread_philo, NULL, routine_philo, &philo) != 0)
		ft_puterr_exit(ERR_THREAD_CREATE);
	if (pthread_join(thread_monitor, NULL) != 0)
		ft_puterr_exit(ERR_THREAD_JOIN);
	if (pthread_join(thread_philo, NULL) != 0)
		ft_puterr_exit(ERR_THREAD_JOIN);
	exit(EXIT_SUCCESS);
}

static void	*routine_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	ft_msleep(philo->start_interval);
	ft_sem_wait(philo->access_sem);
	philo->time_last_eat = get_current_time_in_msec();
	ft_sem_post(philo->access_sem);
	while (1)
	{
		philo_wait_forks(philo);
		philo_eat(philo);
		philo_release_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (args);
}

static void	*routine_monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		ft_sem_wait(philo->access_sem);
		if (philo->time_last_eat != 0
			&& philo->time_to_die < get_time_diff(philo))
		{
			print_log(philo, LOG_DIE);
			ft_sem_post(philo->access_sem);
			exit(EXIT_FAILURE);
		}
		ft_sem_post(philo->access_sem);
		// ft_msleep(MONITOR_INTERVAL);
		ft_msleep(5);
	}
	return (args);
}

static void	set_interval(t_philo *philo)
{
	t_time	total_interval;
	t_time	eat_interval;
	size_t	num_of_fork_sets;

	if (philo->num_of_philo % 2 == 0)
	{
		philo->start_interval = 0;
		return ;
	}
	num_of_fork_sets = philo->num_of_philo / 2;
	eat_interval = philo->time_to_eat / num_of_fork_sets;
	total_interval = 0;
	if (2 < philo->philo_index)
		total_interval = eat_interval * (philo->philo_index / 2);
	if (philo->philo_index % 2 == 0)
		total_interval += philo->time_to_eat;
	philo->start_interval = total_interval;
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
	set_interval(philo);
}
