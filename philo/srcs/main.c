/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:55:27 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/09 19:55:28 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_info		*info;
	pthread_t	monitor;

	info = init_global_info(argc, argv);
	if (info == NULL)
		return (EXIT_FAILURE);
	if (allocate_philo_and_fork(info) != 0)
		return (EXIT_FAILURE);
	if (init_all_mutexes(info) != 0)
		return (EXIT_FAILURE);
	init_philos(info);
	if (create_philo_threads(info) != 0)
		return (EXIT_FAILURE);
	if (create_join_monitor_thread(info, &monitor) != 0)
		return (EXIT_FAILURE);
	if (join_philo_threads(info) != 0)
		return (EXIT_FAILURE);
	destroy_all_mutexes(info);
	free_global_info(info);
	return (EXIT_SUCCESS);
}
