NAME = philo
INC = philosophers.h
FLAGS = -Wall -Wextra -Werror
SRC = philo.c philo_utils.c free_destroy.c routine.c init_mutex_philo.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)
$(NAME) : $(OBJ) $(INC)
	gcc $(FLAGS) $(OBJ) -o $(NAME)
clean:
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME)
re: fclean all