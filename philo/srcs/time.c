#include "philosophers.h"

t_time	get_current_time_in_usec(void)
{
	long long		current_in_usec;
	struct timeval	current;

	if (gettimeofday(&current, NULL) != 0)
		return (-1);
	current_in_usec = current.tv_sec * SEC_TO_MSEC * MSEC_TO_USEC
		+ current.tv_usec;
	return (current_in_usec);
}

t_time	get_current_time_in_msec(void)
{
	long long		current_in_msec;
	struct timeval	current;

	if (gettimeofday(&current, NULL) != 0)
		return (-1);
	current_in_msec = current.tv_sec * SEC_TO_MSEC
		+ current.tv_usec / USEC_TO_MSEC;
	return (current_in_msec);
}

int	ft_usleep(unsigned int usec)
{
	long long	end_time;
	long long	left_time_sleep;

	end_time = get_current_time_in_usec() + usec;
	while (1)
	{
		left_time_sleep = end_time - get_current_time_in_usec();
		if (left_time_sleep <= 0)
			break ;
		usleep(left_time_sleep / 2);
	}
	return (0);
}

int	ft_msleep(unsigned int msec)
{
	long long	end_time;
	long long	left_time_sleep;

	end_time = get_current_time_in_usec() + (msec * MSEC_TO_USEC);
	while (1)
	{
		left_time_sleep = end_time - get_current_time_in_usec();
		if (left_time_sleep <= 0)
			break ;
		usleep(left_time_sleep / 2);
	}
	return (0);
}

long long	get_time_difference(t_philo *philo)
{
	long long	difference;

	difference = get_current_time_in_usec() - philo->last_eat_time_in_usec;
	return (difference);
}
