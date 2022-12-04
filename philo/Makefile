NAME := philo

SRCS_DIR := ./srcs
OBJS_DIR := ./objs

SRCS := main.c \
		cmdline_arguments.c \
		utils.c \
		ft_atoi.c \

OBJS := $(SRCS:.c=.o)
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))

INC_DIR := ./includes
INCLUDES := $(addprefix -I, $(INC_DIR))

CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -rf

.PHONY: all
all: $(NAME)

$(OBJS_DIR)/%o: $(SRCS_DIR)/%c
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

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
