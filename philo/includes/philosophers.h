#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>

# define ERR_MEM "[Error] Couldn't allocate memory"
# define ERR_ARGS "[Error] Invalid argument found in cmdline arguments"
# define ERR_ARG_SIGN "[Error] Each argument must be positive integer number"
# define ERR_MTX_INIT "[Error] Couldn't initialize mutex"
# define ERR_MTX_DESTROY "[Error] Couldn't destroy mutex"
# define ERR_THREAD_CREATE "[Error] Couldn't create threads"
# define ERR_THREAD_JOIN "[Error] Couldn't join threads"
# define ERR_THREAD_DETATCH "[Error] Couldn't detatch threads"
typedef pthread_mutex_t	t_fork;
typedef long long		t_time;
typedef struct s_info	t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	access_mutex;
	pthread_mutex_t	*syslog_mutex;
	t_fork			*right_fork;
	t_fork			*left_fork;
	long long		last_eat_time_in_usec;
	size_t			eat_cnt;
	t_info			*info;
	int				status;
}	t_philo;

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_each_philo_must_eat;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	syslog_mutex;
	bool			is_simulation_stop;
}	t_info;

typedef t_info			t_global_info;

// initializer.c
t_info	*init_global_info(int argc, char **argv);
int		allocate_philo_and_fork(t_info *info);
void	free_global_info(t_info *info);
// cmdline_arguments.c
int		validate_argument_count(int argc);
int		set_cmdline_arguments(int argc, char **argv, t_global_info *info);
int		is_each_cmdline_arguments_valid(t_global_info *info);

// utils.c
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_puterr(char *s);

// ft_atoi.c
int		ft_atoi(const char *str);

#endif
