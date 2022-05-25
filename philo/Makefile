NAME = philo

SRC = 	philo.c \
		ft_atoi.c \
		mutex.c \
		parsing.c \
		time.c \
		create_pthread.c \
		status.c \
		game_over.c \
		routine.c

INCLUDE = -I ./includes
OBJ = $(SRC:%.c=%.o)


CFLAGS = -Wall -Werror -Wextra
DEBUG = #ß-fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) $(DEBUG) -o $(NAME) 

%.o: %.c
	gcc -c  $(INCLUDE) $(CFLAGS) $(DEBUG) $< -o $@

clean:
	# $(MAKE) fclean -C
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all