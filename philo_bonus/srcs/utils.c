#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return ;
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

void	ft_puterr(char *s)
{
	ft_putendl_fd(s, STDERR_FILENO);
}
