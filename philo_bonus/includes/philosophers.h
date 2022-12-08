#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <errno.h>
# include <pthread.h>
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

typedef struct s_info
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_times_must_eat;
}	t_info;

// cmdline_arguments.
int		validate_argument_count(int argc);
int		set_cmdline_arguments(int argc, char **argv, t_info *info);
int		is_each_cmdline_arguments_valid(t_info *info);

// ft_atoi.c
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_puterr(char *s);

#endif