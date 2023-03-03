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

# define ERR_ARG_FORMAT "[Error] Unable to convert some arguments to integer"
# define ERR_ARG_NEGATIVE "[Error] Each arguments must be positive integer value"
# define ERR_ARG_PHILO_NUM "[Error] Num of philos must be less than equal 200"

# define MAX_PHILO_NUM 200

// Command line arguments
typedef struct s_args
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_must_eat;
}	t_args;

// ft_atoi.c
int	ft_atoi(const char *str);

// ft_put_some.c
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_puterr(char *err_msg);

// cmdline_args.c
void	parse_cmdline_arguments(int argc, char **argv, t_args *args);

// validate_args.c
void	validate_arguments(int argc);

#endif
