#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (parse_cmdline_arguments(argc, argv, &info) != 0)
		return (EXIT_FAILURE);
	printf("num_of_philo: %d\n", info.num_of_philo);
	printf("time_to_die: %d\n", info.time_to_die);
	printf("time_to_eat: %d\n", info.time_to_eat);
	printf("time_to_sleep: %d\n", info.time_to_sleep);
	printf("num_of_must_eat: %d\n", info.num_of_must_eat);
	return (EXIT_SUCCESS);
}
