#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <errno.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>

# define ERR_MEM "[Error] Couldn't allocate memory"
# define ERR_ARGS "[Error] Invalid argument found in cmdline arguments"
# define ERR_ARG_SIGN "[Error] Each argument must be positive integer number"

# define SEM_FORK_NAME "forks"
# define SEM_SYSLOG_NAME "syslog"
# define SEM_OFLAG (O_CREAT | O_EXCL)
# define SEM_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

typedef long long	t_time;
# define USEC_TO_MSEC 1000
# define MSEC_TO_SEC 1000
# define SEC_TO_MSEC 1000
# define MSEC_TO_USEC 1000

typedef struct s_info
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_times_must_eat;
	sem_t	*forks;
	sem_t	*sys_log;
}	t_info;

// cmdline_arguments.c
int		validate_argument_count(int argc);
int		set_cmdline_arguments(int argc, char **argv, t_info *info);
int		is_each_cmdline_arguments_valid(t_info *info);

// time.c
t_time	get_current_time_in_usec(void);
t_time	get_current_time_in_msec(void);
int		ft_usleep(unsigned int usec);
int		ft_msleep(unsigned int msec);

// ft_atoi.c
int		ft_atoi(const char *str);

// utils.c
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_puterr(char *s);

#endif