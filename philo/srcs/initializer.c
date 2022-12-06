#include "philosophers.h"

t_global_info	*init_global_info(int argc, char **argv)
{
	t_global_info	*info;

	if (validate_argument_count(argc) != 0)
		return (NULL);
	info = (t_global_info *)malloc(sizeof(t_global_info));
	if (info == NULL)
	{
		ft_puterr(ERR_MEM);
		return (NULL);
	}
	if (set_cmdline_arguments(argc, argv, info) != 0)
	{
		ft_puterr(ERR_ARGS);
		free(info);
		return (NULL);
	}
	if (is_each_cmdline_arguments_valid(info) != 0)
	{
		free(info);
		return (NULL);
	}
	info->is_simulation_stop = false;
	return (info);
}

