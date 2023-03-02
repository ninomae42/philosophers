#include "philo_bonus.h"

static bool	is_argc_valid(int argc)
{
	if (!(argc == 5 || argc == 6))
		return (false);
	return (true);
}

static void	print_usage(void)
{
	ft_putstr_fd("Usage: ./philo number_of_philosophers ", STDERR_FILENO);
	ft_putstr_fd("time_to_die time_to_eat ", STDERR_FILENO);
	ft_putstr_fd("time_to_sleep ", STDERR_FILENO);
	ft_putendl_fd("[number_of_times_each_philosopher_must_eat]", STDERR_FILENO);
}

void	validate_arguments(int argc)
{
	if (!is_argc_valid(argc))
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	(void)argv;
	validate_arguments(argc);
	exit(EXIT_SUCCESS);
}
