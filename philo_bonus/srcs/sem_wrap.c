/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_wrap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:53:56 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/09 19:53:57 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_post(sem_t *sem)
{
	if (sem_post(sem) < 0)
		ft_puterr_exit(ERR_SEM_WAIT);
}

void	ft_sem_wait(sem_t *sem)
{
	if (sem_wait(sem) < 0)
		ft_puterr_exit(ERR_SEM_WAIT);
}
