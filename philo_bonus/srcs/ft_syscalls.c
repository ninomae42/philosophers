#include "philo_bonus.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_puterr_exit(ERR_FORK);
	return (pid);
}

void	ft_kill(pid_t pid, int sig)
{
	if (kill(pid, sig) != 0)
		ft_puterr_exit(ERR_KILL);
}

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (res == NULL)
		ft_puterr_exit(ERR_MEM);
	memset(res, 0, size);
	return (res);
}
