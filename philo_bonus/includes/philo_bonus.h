#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <unistd.h>

// ft_put_some.c
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_puterr(char *err_msg);

#endif
