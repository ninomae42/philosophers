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
	size_t	num_left_fork;
	size_t	num_right_fork;

	sems->philo_access_sems = sem_allocate_all_access_sems(num_of_philo);
	sems->log_sem = sem_create(PHILO_LOG, 1);
	num_right_fork = num_of_philo / 2;
	num_left_fork = num_of_philo / 2;
	if (num_of_philo % 2 != 0)
		num_left_fork = num_left_fork + 1;
	sems->fork_left_sem = sem_create(PHILO_LEFT_FORK, num_left_fork);
	sems->fork_right_sem = sem_create(PHILO_RIGHT_FORK, num_right_fork);
}

void	sem_deallocate_all_sems(t_sems *sems, size_t num_of_philo)
{
	size_t	i;

	sem_close(sems->log_sem);
	sem_close(sems->fork_left_sem);
	sem_close(sems->fork_right_sem);
	i = 0;
	while (i < (size_t)num_of_philo)
	{
		sem_close(sems->philo_access_sems[i]);
		i++;
	}
	free(sems->philo_access_sems);
}
