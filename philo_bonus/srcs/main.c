/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:53:22 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/10 20:10:57 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_args	args;
	t_sems	sems;

setvbuf(stdout, NULL, _IOLBF, 0);
	validate_arguments(argc);
	parse_cmdline_arguments(argc, argv, &args);
	sem_allocate_all_sems(&sems, args.num_of_philo);
	if (make_wait_procs(&args, &sems) < 0)
	{
		sem_deallocate_all_sems(&sems, args.num_of_philo);
		exit(EXIT_FAILURE);
	}
	sem_deallocate_all_sems(&sems, args.num_of_philo);
	exit(EXIT_SUCCESS);
}

// If redirection needed add below to the head of main
// setvbuf(stdout, NULL, _IOLBF, 0);
