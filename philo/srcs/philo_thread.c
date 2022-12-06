#include "philosophers.h"

static int	create_thread_inner(t_info *info, size_t *index);

int	create_philo_threads(t_info *info)
{
	size_t	i;

	if (create_thread_inner(info, &i) != 0)
	{
		ft_puterr(ERR_THREAD_CREATE);
		detach_all_threads(info, i);
		destroy_all_mutexes(info);
		free_global_info(info);
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
		destroy_all_mutexes(info);
		free_global_info(info);
		return (1);
	}
	return (0);
}

static int	create_thread_inner(t_info *info, size_t *index)
{
	size_t	i;

	i = 0;
	if (info->num_of_philo == 1)
	{
		if (pthread_create(&(info->philos[i].thread), NULL,
				&routine_single_philo, (void *)&(info->philos[i])) != 0)
		{
			*index = i;
			return (1);
		}
	}
	while (i < (size_t)info->num_of_philo)
	{
		if (pthread_create(&(info->philos[i].thread), NULL,
				&routine_philo, (void *)&(info->philos[i])) != 0)
		{
			*index = i;
			return (1);
		}
		i++;
	}
	return (0);
}
