NAME := philo_bonus

SRCS_DIR := ./srcs
OBJS_DIR := ./objs

SRCS := main.c \
		cmdline_args.c \
		validate_args.c \
		sem_create.c \
		sem_allocate.c \
		sem_wrap.c \
		philo_action.c \
		philo_action2.c \
		philo_do_proc.c \
		philo_main_routine.c \
		philo_monitor_routine.c \
		procs.c \
		time.c \
		ft_atoi.c \
		ft_itoa.c \
		ft_calloc.c \
		ft_strjoin.c \
		ft_put_some.c \

OBJS := $(SRCS:.c=.o)
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))

INC_DIR := ./includes
INCLUDES := $(addprefix -I, $(INC_DIR))

LIBS := pthread
LFLAGS := $(addprefix -l, $(LIBS))

CC := cc
CFLAGS := -Wall -Wextra -Werror
# CFLAGS += -g
# CFLAGS += -fsanitize=undefined
# CFLAGS += -fsanitize=address
# CFLAGS += -fsanitize=thread
RM := rm -rf

.PHONY: all
all: $(NAME)

$(OBJS_DIR)/%o: $(SRCS_DIR)/%c
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

.PHONY: clean
clean:
	$(RM) $(OBJS_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: norm
norm:
	-@norminette includes/ | grep -v "INVALID_HEADER"
	-@norminette srcs/ | grep -v "INVALID_HEADER"
