#include "philo_bonus.h"

void	print_log(t_philo *philo, t_log_type log_type, t_time log_time)
{
	sem_wait(philo->log_sem);
	if (log_type == LOG_FORK)
		printf("%lld %zu has taken a fork\n",
				log_time, philo->philo_index);
	else if (log_type == LOG_EAT)
		printf("%lld %zu is eating\n",
				log_time, philo->philo_index);
	else if (log_type == LOG_SLEEP)
		printf("%lld %zu is sleeping\n",
				log_time, philo->philo_index);
	else if (log_type == LOG_THINK)
		printf("%lld %zu is thinking\n",
				log_time, philo->philo_index);
	else if (log_type == LOG_DIE)
	{
		printf("%lld %zu is died\n",
				log_time, philo->philo_index);
		return ;
	}
	sem_post(philo->log_sem);
}
