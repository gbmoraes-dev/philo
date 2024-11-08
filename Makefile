NAME = philo

SRCS = main.c utils.c init.c
SRCS += dinner.c check_threads.c get_set.c
SRCS += monitor.c mutex_and_thread_handle.c validate_and_parse.c

SRCS := $(addprefix ./src/, $(SRCS))

LIBFT_PATH = ./lib/libft

LIBFT = $(LIBFT_PATH)/libft.a

CC = gcc -pthread

CFLAGS = -Wall -Wextra -Werror

MAKEFLAGS += --no-print-directory

LIBFT_LINK = -L$(LIBFT_PATH) -lft

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIBFT_LINK)

$(LIBFT):
	@make -C $(LIBFT_PATH)

clean:
	@rm -f $(NAME)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@make fclean -C $(LIBFT_PATH)

re: clean all

.PHONY:
	all re clean fclean
