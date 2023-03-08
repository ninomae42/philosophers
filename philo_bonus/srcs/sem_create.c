#include "philo_bonus.h"

static sem_t	*ft_sem_open(char *name, unsigned int value)
{
	sem_t		*sem;
	const int	sem_oflag = O_CREAT | O_EXCL;
	const int	sem_mode = S_IRUSR | S_IWUSR
		| S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	sem = sem_open(name, sem_oflag, sem_mode, value);
	if (sem == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			sem = sem_open(name, O_RDWR);
			if (sem == SEM_FAILED)
				return (SEM_FAILED);
			sem_close(sem);
			sem_unlink(name);
			sem = sem_open(name, sem_oflag, sem_mode, value);
		}
	}
	return (sem);
}

sem_t	*sem_create(char *sem_name, unsigned int value)
{
	sem_t	*sem;

	sem = ft_sem_open(sem_name, value);
	if (sem == SEM_FAILED)
		ft_puterr_exit(ERR_SEM_OPEN);
	sem_unlink(sem_name);
	return (sem);
}

sem_t	*sem_create_access(size_t index)
{
	sem_t	*sem;
	char	*sem_name;
	char	*sem_index;

	sem_index = ft_itoa(index);
	sem_name = ft_strjoin(PHILO_ACCESS_SEM_PREFIX, sem_index);
	sem = ft_sem_open(sem_name, 1);
	if (sem == SEM_FAILED)
	{
		free(sem_name);
		free(sem_index);
		ft_puterr_exit(ERR_SEM_OPEN);
	}
	sem_unlink(sem_name);
	free(sem_index);
	free(sem_name);
	return (sem);
}
