#include "philo_bonus.h"

void	ft_sem_post(sem_t *sem)
{
	if (sem_post(sem) < 0)
		ft_puterr_exit(ERR_SEM_WAIT);
}

void	ft_sem_wait(sem_t *sem)
{
	if (sem_wait(sem) < 0)
		ft_puterr_exit(ERR_SEM_WAIT);
}
