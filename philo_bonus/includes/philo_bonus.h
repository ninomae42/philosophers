#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <errno.h>
# include <fcntl.h>
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

// --- Constants ---
// Error Messages
# define ERR_ARG_FORMAT "[Error] Unable to convert some arguments to integer"
# define ERR_ARG_NEGATIVE "[Error] Each arguments must be positive integer value"
# define ERR_ARG_PHILO_NUM "[Error] Num of philos must be less than equal 200"
# define ERR_FORK "[Error] Unable to fork process"
# define ERR_KILL "[Error] Unable to kill signal"
# define ERR_MEM "[Error] Unable to allocate memory"
# define ERR_GET_TIME "[Error] gettimeofday."

// 1 milliseconds is equal to 1000 microseconds
# define USEC_TO_MSEC 1000
# define MSEC_TO_USEC 1000

// 1 seconds is equal to 1000 milliseconds
# define MSEC_TO_SEC 1000
# define SEC_TO_MSEC 1000

// Program constraints
# define MAX_PHILO_NUM 200

// Monitoring interval
# define MONITOR_INTERVAL 500

// --- Types ---
// Command line arguments
typedef struct s_args
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_must_eat;
}	t_args;

// Time
typedef long long	t_time;

// philo thread information
typedef struct s_philo
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_must_eat;

	sem_t	*log_sem;
	sem_t	*fork_left_sem;
	sem_t	*fork_right_sem;

	sem_t	*access_sem;
	size_t	philo_index;
	t_time	time_last_eat;
	int		num_of_current_eat;
	bool	is_simulation_stop;
	bool	is_philo_success;
}	t_philo;

typedef enum e_log_type
{
	LOG_FORK = 0,
	LOG_EAT = 1,
	LOG_SLEEP = 2,
	LOG_THINK = 3,
}	t_log_type;


// ft_atoi.c
int		ft_atoi(const char *str);

// ft_put_some.c
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_puterr(char *err_msg);
void	ft_puterr_exit(char *err_msg);

// cmdline_args.c
void	parse_cmdline_arguments(int argc, char **argv, t_args *args);

// validate_args.c
void	validate_arguments(int argc);

// time.c
t_time	get_current_time_in_usec(void);
t_time	get_current_time_in_msec(void);
t_time	get_time_diff(t_philo *philo);
void	ft_usleep(unsigned int usec);
void	ft_msleep(unsigned int msec);

#endif
