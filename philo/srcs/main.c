#include "philosophers.h"

t_global_info	*init_global_info(int argc, char **argv)
{
	t_global_info	*info;

	if (validate_argument_count(argc) != 0)
		return (NULL);
	info = (t_global_info *)malloc(sizeof(t_global_info));
	if (info == NULL)
	{
		ft_puterr("[Error] Couldn't allocate memory");
		return (NULL);
	}
	if (set_cmdline_arguments(argc, argv, info) != 0)
	{
		ft_puterr("[Error] Invalid argument found"
			"somewhere in cmdline arguments");
		free(info);
		return (NULL);
	}
	if (is_each_cmdline_arguments_valid(info) != 0)
	{
		free(info);
		return (NULL);
	}
	return (info);
}

int	main(int argc, char **argv)
{
	t_info		*info;

	info = init_global_info(argc, argv);
	if (info == NULL)
		return (EXIT_FAILURE);
	if (allocate_philo_and_fork(info) != 0)
		return (EXIT_FAILURE);
	if (init_all_mutexes(info) != 0)
		return (EXIT_FAILURE);
	init_philos(info);
	if (create_philo_threads(info) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
