NAME = philo_one

CC = gcc
LIB = -lpthread

HEADER_DIR = -I.
CFLAGS = -Wall -Wextra -Werror $(HEADER_DIR)

SRCS = main.c utils.c init.c thread.c thread_utils.c get_mutex.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LIB) $(CFLAGS) $(SRCS) -o $(NAME)

bonus: all

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:all clean fclean re
