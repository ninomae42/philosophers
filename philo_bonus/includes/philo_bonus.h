/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:52:45 by tashimiz          #+#    #+#             */
/*   Updated: 2023/03/22 16:17:12 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// --- Constants ---
// Error Messages
# define ERR_ARG_FORMAT "[Error] Unable to convert some arguments to integer"
# define ERR_ARG_NEGATIVE "[Error] Each arguments must be positive integer"
# define ERR_ARG_PHILO_NUM "[Error] Num of philos must be 1 <= num <= 200"
# define ERR_ARG_TIME "[Error] Max time duration is less than equal to 10000"
# define ERR_FORK "[Error] Unable to fork process"
# define ERR_KILL "[Error] Unable to kill signal"
# define ERR_MEM "[Error] Unable to allocate memory"
# define ERR_WAIT "[Error] Unable to wait procs"
# define ERR_GET_TIME "[Error] gettimeofday."
# define ERR_SEM_OPEN "[Error] Unable to create semaphore"
# define ERR_SEM_POST "[Error] Unable to post semaphore"
# define ERR_SEM_WAIT "[Error] Unable to wait semaphore"
# define ERR_THREAD_CREATE "[Error] Unable to craete thread"
# define ERR_THREAD_JOIN "[Error] Unable to join thread"

// 1 milliseconds is equal to 1000 microseconds
# define USEC_TO_MSEC 1000
# define MSEC_TO_USEC 1000

// 1 seconds is equal to 1000 milliseconds
# define MSEC_TO_SEC 1000
# define SEC_TO_MSEC 1000

// Program constraints
# define MIN_PHILO_NUM 1
# define MAX_PHILO_NUM 200
# define MAX_TIME_DURATION 10000

// Monitoring interval
# define MONITOR_INTERVAL 5

// Semaphore Names
# define PHILO_LOG "/sem_syslog"
# define PHILO_FORK "/sem_fork"
# define PHILO_PRE_FORK "/sem_pre_fork"
# define PHILO_ACCESS_SEM_PREFIX "/sem_sync"

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
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_must_eat;
	int		time_to_think;

	sem_t	*log_sem;
	sem_t	*fork_sem;
	sem_t	*pre_fork_sem;

	sem_t	*access_sem;
	size_t	philo_index;
	t_time	time_last_eat;
	int		num_of_current_eat;
	bool	is_simulation_stop;
	bool	is_simulation_success;

	time_t	start_interval;
}	t_philo;

// semaphore management
typedef struct s_sems
{
	sem_t	*log_sem;
	sem_t	*fork_sem;
	sem_t	*pre_fork_sem;
	sem_t	**philo_access_sems;
}	t_sems;

typedef enum e_log_type
{
	LOG_FORK = 0,
	LOG_EAT = 1,
	LOG_SLEEP = 2,
	LOG_THINK = 3,
	LOG_DIE = 4,
}	t_log_type;

// cmdline_args.c
void	parse_cmdline_arguments(int argc, char **argv, t_args *args);

// validate_args.c
void	validate_arguments(int argc);

// sem_craete.c
sem_t	*sem_create(char *sem_name, unsigned int value);
sem_t	*sem_create_access(size_t index);

// sem_allocate.c
void	sem_allocate_all_sems(t_sems *sems, int num_of_philo);
void	sem_deallocate_all_sems(t_sems *sems, size_t num_of_philo);

// sem_wrap.c
void	ft_sem_post(sem_t *sem);
void	ft_sem_wait(sem_t *sem);

// philo_action.c
int		philo_wait_forks(t_philo *philo);
void	philo_release_forks(t_philo *philo);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);

// philo_action2.c
int		print_log(t_philo *philo, t_log_type log_type);
bool	philo_is_philo_dead(t_philo *philo);

// philo_do_proc.c
void	do_philo_proc(size_t index, t_args *arg, t_sems *sem);

// philo_main_routine.c
void	*routine_monitor(void *args);

// philo_monitor_routine.c
void	*routine_philo(void *args);
void	*routine_single_philo(void *args);

// procs.c
int		make_wait_procs(t_args *arg, t_sems *sem);

// time.c
t_time	get_current_time_in_usec(void);
t_time	get_current_time_in_msec(void);
t_time	get_time_diff(t_philo *philo);
void	ft_usleep(unsigned int usec);
void	ft_msleep(unsigned int msec);

// ft_calloc.c
void	*ft_calloc(size_t count, size_t size);

// ft_itoa.c
char	*ft_itoa(int n);

// ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

// ft_atoi.c
int		ft_atoi(const char *str);

// ft_put_some.c
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_puterr(char *err_msg);
void	ft_puterr_exit(char *err_msg);
size_t	ft_strlen(char *s);

#endif
