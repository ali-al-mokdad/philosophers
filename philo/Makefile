NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g  -I$(INCLUDES)
INCLUDES = -I./includes

SRCS = main.c \
	

OBJECTS = $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) 


clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
