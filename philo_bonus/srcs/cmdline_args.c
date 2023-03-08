#include "philo_bonus.h"

static int	is_each_arguments_valid(t_args *args);
static int	do_atoi_set_safely(char *s, int *dst);
static int	set_cmdline_arguments(int argc, char **argv, t_args *args);

void	parse_cmdline_arguments(int argc, char **argv, t_args *args)
{
	int	res;

	memset(args, 0, sizeof(t_args));
	if (set_cmdline_arguments(argc, argv, args) != 0)
	{
		ft_puterr(ERR_ARG_FORMAT);
		exit(EXIT_FAILURE);
	}
	res = is_each_arguments_valid(args);
	if (res != 0)
	{
		if (res == 1)
			ft_puterr(ERR_ARG_NEGATIVE);
		else if (res == 2)
			ft_puterr(ERR_ARG_PHILO_NUM);
		exit(EXIT_FAILURE);
	}
}

static int	is_each_arguments_valid(t_args *args)
{
	if (args->num_of_philo < 1 || args->time_to_die < 0
		|| args->time_to_eat < 0 || args->time_to_sleep < 0
		|| args->num_of_must_eat < 0)
		return (1);
	if (MAX_PHILO_NUM < args->num_of_philo)
		return (2);
	return (0);
}

static int	do_atoi_set_safely(char *s, int *dst)
{
	int	ret;

	errno = 0;
	ret = ft_atoi(s);
	if (errno != 0)
		return (1);
	*dst = ret;
	return (0);
}

static int	set_cmdline_arguments(int argc, char **argv, t_args *args)
{
	if (do_atoi_set_safely(argv[1], &args->num_of_philo) != 0)
		return (1);
	if (do_atoi_set_safely(argv[2], &args->time_to_die) != 0)
		return (1);
	if (do_atoi_set_safely(argv[3], &args->time_to_eat) != 0)
		return (1);
	if (do_atoi_set_safely(argv[4], &args->time_to_sleep) != 0)
		return (1);
	if (argc == 6)
	{
		if (do_atoi_set_safely(argv[5], &args->num_of_must_eat) != 0)
		return (1);
	}
	else
		args->num_of_must_eat = 0;
	return (0);
}

