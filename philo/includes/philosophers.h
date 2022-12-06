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
