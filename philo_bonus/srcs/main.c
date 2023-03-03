#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_args	args;

	validate_arguments(argc);
	parse_cmdline_arguments(argc, argv, &args);
	exit(EXIT_SUCCESS);
}
