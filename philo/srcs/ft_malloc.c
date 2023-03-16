#include "philosophers.h"

void	*ft_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	memset(ret, 0, size);
	return (ret);
}
