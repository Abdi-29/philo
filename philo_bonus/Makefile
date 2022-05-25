NAME = philo_bonus

SRC = 	philo.c \
		ft_atoi.c \
		mutex.c \
		parsing.c \
		time.c \
		create_pthread.c \
		status.c \
		game_over.c \
		routine.c \
		time_eat.c

INCLUDE = -I ./includes
OBJ = $(SRC:%.c=%.o)


CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) 

%.o: %.c
	gcc -c  $(INCLUDE) $(CFLAGS) $(DEBUG) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all