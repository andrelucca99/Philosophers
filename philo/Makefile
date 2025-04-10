NAME = philo
SRCS = ./src/main.c ./src/init.c ./src/monitor.c ./src/routine.c ./src/safe_functions.c ./src/utils.c ./src/threads.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
