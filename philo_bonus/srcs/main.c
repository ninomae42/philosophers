#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_args	args;
	t_sems	sems;

	validate_arguments(argc);
	parse_cmdline_arguments(argc, argv, &args);
	sem_allocate_all_sems(&sems, args.num_of_philo);
	do_philo_proc(1, &args, &sems);
	sem_deallocate_all_sems(&sems, args.num_of_philo);
	exit(EXIT_SUCCESS);
}
