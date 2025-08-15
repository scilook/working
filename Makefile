CC = cc
CF = -g -Wall -Werror -Wextra #-fsanitize=address
SRCS = philo.c philo_action.c philo_utils.c philo_lock.c
OBJS = $(SRCS:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CF) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CF) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
