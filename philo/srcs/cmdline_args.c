#include "philosophers.h"

static void	print_usage(void);
static int	do_atoi_set_safe(char *s, int *dst);
static int	set_cmdline_arguments(int argc, char **argv, t_info *info);
static int	is_each_cmdline_arguments_valid(t_info *info);

int	parse_cmdline_arguments(int argc, char **argv, t_info *info)
{
	if (!(argc == 5 || argc == 6))
	{
		print_usage();
		return (1);
	}
	if (set_cmdline_arguments(argc, argv, info) != 0)
	{
		ft_puterr(ERR_ARG_FORMAT);
		return (1);
	}
	if (is_each_cmdline_arguments_valid(info) != 0)
		return (1);
	return (0);
}

static int	set_cmdline_arguments(int argc, char **argv, t_info *info)
{
	if (do_atoi_set_safe(argv[1], &(info->num_of_philo)) != 0)
		return (1);
	if (do_atoi_set_safe(argv[2], &(info->time_to_die)) != 0)
		return (1);
	if (do_atoi_set_safe(argv[3], &(info->time_to_eat)) != 0)
		return (1);
	if (do_atoi_set_safe(argv[4], &(info->time_to_sleep)) != 0)
		return (1);
	info->num_of_must_eat = 0;
	if (argc == 6)
		if (do_atoi_set_safe(argv[5], &(info->num_of_must_eat)) != 0)
			return (1);
	return (0);
}

static int	is_each_cmdline_arguments_valid(t_info *info)
{
	if (info->num_of_philo < 1 || info->time_to_die < 0
		|| info->time_to_eat < 0 || info->time_to_sleep < 0
		|| info->num_of_must_eat < 0)
	{
		ft_puterr(ERR_ARG_NEGATIVE);
		return (1);
	}
	return (0);
}

static int	do_atoi_set_safe(char *s, int *dst)
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
