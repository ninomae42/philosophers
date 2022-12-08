#include "philosophers.h"

t_info	*init_global_info(int argc, char **argv)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL)
		return (NULL);
	if (validate_argument_count(argc) != 0)
	{
		free(info);
		return (NULL);
	}
	if (set_cmdline_arguments(argc, argv, info) != 0)
	{
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
	t_info	*info;

	info = init_global_info(argc, argv);
	if (info == NULL)
		exit(EXIT_FAILURE);
	printf("num_philo: %d\n", info->num_of_philo);
	printf("time_to_die: %d\n", info->time_to_die);
	printf("time_to_eat: %d\n", info->time_to_eat);
	printf("time_to_sleep: %d\n", info->time_to_sleep);
	printf("min_eat_cnt: %d\n", info->num_of_times_must_eat);
	free(info);
	exit(EXIT_SUCCESS);
}
