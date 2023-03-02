#include "philo_bonus.h"

static size_t	ft_strlen(char *s)
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
