/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:25:32 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/16 23:25:33 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_info		info;
	pthread_t	monitor;

	if (parse_cmdline_arguments(argc, argv, &info) != 0)
		return (EXIT_FAILURE);
	if (allocate_philo_and_fork(&info) != 0)
		return (EXIT_FAILURE);
	if (init_all_mutex(&info) < 0)
		return (EXIT_FAILURE);
	set_philo_info(&info);
	if (create_philo_thread(&info) != 0)
		return (EXIT_FAILURE);
	if (create_and_join_monitor_thread(&info, &monitor) != 0)
		return (EXIT_FAILURE);
	if (join_philo_threads(&info) != 0)
		return (EXIT_FAILURE);
	destroy_all_mutex(&info);
	deallocate_philo_and_fork(&info);
	return (EXIT_SUCCESS);
}
