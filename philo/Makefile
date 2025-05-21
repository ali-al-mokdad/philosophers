NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c routine.c init.c monitor.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

