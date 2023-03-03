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
# include <signal.h>
# include <string.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <unistd.h>

# define ERR_ARG_FORMAT "[Error] Unable to convert some arguments to integer"
# define ERR_ARG_NEGATIVE "[Error] Each arguments must be positive integer value"
# define ERR_ARG_PHILO_NUM "[Error] Num of philos must be less than equal 200"
# define ERR_FORK "[Error] Unable to fork process"
# define ERR_KILL "[Error] Unable to kill signal"
# define ERR_MEM "[Error] Unable to allocate memory"

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
int		ft_atoi(const char *str);

// ft_put_some.c
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_puterr(char *err_msg);
void	ft_puterr_exit(char *err_msg);

// ft_syscalls.c
pid_t	ft_fork(void);
void	ft_kill(pid_t pid, int sig);
void	*ft_malloc(size_t size);

// cmdline_args.c
void	parse_cmdline_arguments(int argc, char **argv, t_args *args);

// validate_args.c
void	validate_arguments(int argc);

#endif
