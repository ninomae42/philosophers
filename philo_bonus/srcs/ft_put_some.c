/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_some.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:53:13 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/09 19:53:14 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	while (SSIZE_MAX < len)
	{
		write(fd, s, SSIZE_MAX);
		s += SSIZE_MAX;
		len -= SSIZE_MAX;
	}
	write(fd, s, len);
}

void	ft_putendl_fd(char *s, int fd)
{
	char	endl;

	endl = '\n';
	ft_putstr_fd(s, fd);
	write(fd, &endl, sizeof(char));
}

void	ft_puterr(char *err_msg)
{
	ft_putendl_fd(err_msg, STDERR_FILENO);
}

void	ft_puterr_exit(char *err_msg)
{
	ft_puterr(err_msg);
	exit(EXIT_FAILURE);
}
