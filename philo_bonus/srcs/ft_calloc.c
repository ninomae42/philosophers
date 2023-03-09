/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:53:03 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/09 19:53:04 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (count == 0 || size == 0)
	{
		count = 0;
		size = 0;
	}
	if (SIZE_MAX / count < size)
		return (NULL);
	ret = malloc(size * count);
	if (ret == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	memset(ret, 0, count * size);
	return (ret);
}
