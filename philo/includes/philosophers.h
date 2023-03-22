/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:25:04 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/22 15:55:32 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// --- Constants ---
// Error Messages
# define ERR_ARG_FORMAT "[Error] Unable to convert some arguments to integer"
# define ERR_ARG_NEGATIVE "[Error] Each arguments must be positive integer"
# define ERR_MEM "[Error] Unable to allocate memory"
# define ERR_MTX_INIT "[Error] Couldn't initialize mutex"
# define ERR_MTX_DESTROY "[Error] Couldn't destroy mutex"
# define ERR_THREAD_CREATE "[Error] Couldn't create threads"
# define ERR_THREAD_JOIN "[Error] Couldn't join threads"
# define ERR_THREAD_DETATCH "[Error] Couldn't detatch threads"
# define ERR_GET_TIME "[Error] gettimeofday."

// 1 milliseconds is equal to 1000 microseconds
# define USEC_TO_MSEC 1000
# define MSEC_TO_USEC 1000

// 1 seconds is equal to 1000 milliseconds
# define MSEC_TO_SEC 1000
# define SEC_TO_MSEC 1000

typedef long long		t_time;
typedef struct s_philo	t_philo;

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;

	pthread_mutex_t	syslog_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*access_mutexes;
	bool			is_simulation_stop;
}	t_info;

typedef struct s_philo
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;

	size_t			id;
	pthread_t		thread;
	pthread_mutex_t	*access_mutex;
	pthread_mutex_t	*syslog_mutex;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;

	t_time			start_interval;
	t_time			last_eat_time;
	int				time_to_think;
	size_t			eat_cnt;
	t_info			*info;
}	t_philo;

typedef enum e_log_type
{
	LOG_FORK = 0,
	LOG_EAT = 1,
	LOG_SLEEP = 2,
	LOG_THINK = 3,
	LOG_DIE = 4,
}	t_log_type;

// cmdline_args.c
int		parse_cmdline_arguments(int argc, char **argv, t_info *info);

// info_alloc.c
int		allocate_philo_and_fork(t_info *info);
void	deallocate_philo_and_fork(t_info *info);

// mutex_init.c
int		init_all_mutex(t_info *info);
void	destroy_all_mutex(t_info *info);

// philo_set_info.c
void	set_philo_info(t_info *info);

// philo_thread_init.c
int		create_philo_thread(t_info *info);
int		join_philo_threads(t_info *info);
void	detach_philo_threads(t_info *info, size_t n);

// philo_routine.c
void	*routine_philo(void *args);
void	*routine_single_philo(void *args);

// philo_actions.c
int		philo_wait_forks(t_philo *philo);
void	philo_release_forks(t_philo *philo);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);

// philo_actions2.c
int		print_philo_log(t_philo *philo, t_log_type log_type);
bool	philo_is_philo_dead(t_philo *philo);

// philo_monitor.c
int		create_and_join_monitor_thread(t_info *info, pthread_t *monitor);

// time.c
t_time	get_current_time_in_usec(void);
t_time	get_current_time_in_msec(void);
t_time	get_time_diff(t_philo *philo);
void	ft_usleep(unsigned int usec);
void	ft_msleep(unsigned int msec);

// ft_atoi.c
int		ft_atoi(const char *str);

// ft_malloc.c
void	*ft_malloc(size_t size);

// ft_put_utils.c
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_puterr(char *s);

#endif
