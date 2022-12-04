#include "philosophers.h"

static int	do_atoi_and_set_safely(char *s, int *dst);
static void	print_usage(void);

int	validate_argument_count(int argc)
{
	if (argc != 5 && argc != 6)
	{
		print_usage();
		return (1);
	}
	return (0);
}

int	set_cmdline_arguments(int argc, char **argv, t_global_info *info)
{
	if (do_atoi_and_set_safely(argv[1], &(info->num_of_philo)) != 0)
		return (1);
	if (do_atoi_and_set_safely(argv[2], &(info->time_to_die)) != 0)
		return (1);
	if (do_atoi_and_set_safely(argv[3], &(info->time_to_eat)) != 0)
		return (1);
	if (do_atoi_and_set_safely(argv[4], &(info->time_to_sleep)) != 0)
		return (1);
	if (argc == 6)
	{
		if (do_atoi_and_set_safely(argv[5],
				&(info->num_of_times_each_philo_must_eat)) != 0)
			return (1);
	}
	else
		info->num_of_times_each_philo_must_eat = 0;
	return (0);
}

int	is_each_cmdline_arguments_valid(t_global_info *info)
{
	if (info->num_of_philo < 0 || info->time_to_die < 0
		|| info->time_to_eat < 0 || info->time_to_sleep < 0
		|| info->num_of_times_each_philo_must_eat < 0)
	{
		ft_puterr(
			"[Error] each argument must be a positive integer number");
		return (1);
	}
	return (0);
}

static int	do_atoi_and_set_safely(char *s, int *dst)
{
	int	ret;

	errno = 0;
	ret = ft_atoi(s);
	if (errno != 0)
		return (1);
	*dst = ret;
	return (0);
}

static void	print_usage(void)
{
	ft_putstr_fd("Usage: ./philo number_of_philosophers ", STDERR_FILENO);
	ft_putstr_fd("time_to_die time_to_eat ", STDERR_FILENO);
	ft_putstr_fd("time_to_sleep ", STDERR_FILENO);
	ft_putendl_fd("[number_of_times_each_philosopher_must_eat]", STDERR_FILENO);
}
