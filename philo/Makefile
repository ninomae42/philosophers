# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 23:26:35 by tashimiz          #+#    #+#              #
#    Updated: 2023/03/16 23:26:36 by tashimiz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

SRCS_DIR := ./srcs
OBJS_DIR := ./objs

SRCS := main.c \
		cmdline_args.c \
		info_alloc.c \
		mutex_init.c \
		philo_action.c \
		philo_action2.c \
		philo_routine.c \
		philo_set_info.c \
		philo_thread_init.c \
		philo_monitor.c \
		time.c \
		ft_atoi.c \
		ft_malloc.c \
		ft_put_utils.c \

OBJS := $(SRCS:.c=.o)
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))

INC_DIR := ./includes
INCLUDES := $(addprefix -I, $(INC_DIR))

CC := cc
CFLAGS := -Wall -Wextra -Werror
# CFLAGS += -g
# CFLAGS += -fsanitize=undefined
# CFLAGS += -fsanitize=address
# CFLAGS := -Wall -Wextra -Werror -g -fsanitize=thread
LDFLAGS := -lpthread
RM := rm -rf

.PHONY: all
all: $(NAME)

$(OBJS_DIR)/%o: $(SRCS_DIR)/%c
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

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
