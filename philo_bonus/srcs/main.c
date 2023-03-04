#include "philo_bonus.h"

void	terminate_procs(pid_t *pid, size_t proc_num)
{
	size_t	i;

	i = 0;
	while (i < proc_num)
	{
		kill(pid[i], SIGTERM);
		i++;
	}
}

pid_t	*make_procs(size_t proc_num)
{
	size_t	i;
	pid_t	*pid;

	i = 0;
	pid = (pid_t *)malloc(sizeof(pid_t) * proc_num);
	if (pid == NULL)
		return (NULL);
	while (i < proc_num)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			ft_puterr("[Error]: Unable to fork process");
			terminate_procs(pid, i);
			return (NULL);
		}
		else if (pid[i] == 0)
		{
			// TODO: do child process
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	return (pid);
}

int	wait_procs(pid_t *pid, size_t proc_num)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < proc_num)
	{
		if (waitpid(pid[i], &status, 0) == -1)
		{
			ft_puterr("[Error] waitpid. Unable to wait procs");
			terminate_procs(pid, proc_num);
			return (1);
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			printf("Child process %d exited with status %d\n", pid[i], WEXITSTATUS(status));
			terminate_procs(pid, proc_num);
			printf("All child process have terminated\n");
			return (1);
		}
		else
			printf("Child process %d exited with status %d\n", pid[i], WEXITSTATUS(status));
		i++;
	}
	printf("All child process have exited successfully\n");
	return (0);
}

int	make_wait_procs(size_t proc_num)
{
	int		res;
	pid_t	*pid;

	pid = make_procs(proc_num);
	if (pid == NULL)
		return (1);
	res = wait_procs(pid, proc_num);
	free(pid);
	if (res != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	args;

	validate_arguments(argc);
	parse_cmdline_arguments(argc, argv, &args);
	if (make_wait_procs(args.num_of_philo) != 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
