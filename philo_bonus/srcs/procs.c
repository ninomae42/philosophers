#include "philo_bonus.h"

static void		terminate_procs(pid_t *pid, size_t proc_num);
static pid_t	*make_procs(size_t proc_num, t_args *arg, t_sems *sem);
static int		wait_procs(pid_t *pid, size_t proc_num);

int	make_wait_procs(t_args *arg, t_sems *sem)
{
	int		res;
	pid_t	*pids;

	pids = make_procs(arg->num_of_philo, arg, sem);
	if (pids == NULL)
		return (1);
	res = wait_procs(pids, arg->num_of_philo);
	free(pids);
	if (res != 0)
		return (1);
	return (0);
}

static void	terminate_procs(pid_t *pid, size_t proc_num)
{
	size_t	i;

	i = 0;
	while (i < proc_num)
	{
		kill(pid[i], SIGTERM);
		i++;
	}
}

static pid_t	*make_procs(size_t proc_num, t_args *arg, t_sems *sem)
{
	size_t	i;
	pid_t	*pid;

	i = 0;
	pid = (pid_t *)malloc(sizeof(pid_t) * proc_num);
	if (pid == NULL)
	{
		ft_puterr(ERR_MEM);
		return (NULL);
	}
	while (i < proc_num)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			ft_puterr(ERR_FORK);
			terminate_procs(pid, i);
			return (NULL);
		}
		else if (pid[i] == 0)
			do_philo_proc(i + 1, arg, sem);
		i++;
	}
	return (pid);
}

static int	wait_procs(pid_t *pid, size_t proc_num)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < proc_num)
	{
		if (waitpid(0, &status, 0) == -1)
		{
			ft_puterr(ERR_WAIT);
			terminate_procs(pid, proc_num);
			return (-1);
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			terminate_procs(pid, proc_num);
			return (-1);
		}
		i++;
	}
	return (0);
}
