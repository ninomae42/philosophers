#include "philosophers.h"

t_info	*init_philosopher(int argc, char **argv)
{
	t_info	*info;

	if (validate_argument_count(argc) != 0)
		return (NULL);
	info = (t_info *)malloc(sizeof(t_info));
	if (info == NULL)
	{
		ft_puterr("Couldn't allocate memory");
		return (NULL);
	}
	if (set_cmdline_arguments(argc, argv, info) != 0)
	{
		ft_puterr("Invalid argument found somewhere in cmdline arugments");
		free(info);
		return (NULL);
	}
	return (info);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = init_philosopher(argc, argv);
	if (info == NULL)
		return (EXIT_FAILURE);
	printf("num_of_philo: %d\n", info->num_of_philo);
	printf("time_to_die: %d\n", info->time_to_die);
	printf("time_to_eat: %d\n", info->time_to_eat);
	printf("time_to_sleep: %d\n", info->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat: %d\n", \
			info->num_of_times_each_philo_must_eat);
	return (EXIT_SUCCESS);
}
