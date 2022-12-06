#include "philosophers.h"

int	detach_all_threads(t_info *info, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_detach(info->philos[i].thread) != 0)
		{
			ft_puterr(ERR_THREAD_DETATCH);
			return (1);
		}
		i++;
	}
	return (0);
}

