NAME = philo_bonus
INC = philo_bonus.h
FLAGS = -Wall -Wextra -Werror
SRC = philo_bonus.c philo_utils_bonus.c routine_bonus.c init_sems_philo_bonus.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)
$(NAME) : $(OBJ) $(INC)
	gcc $(FLAGS) $(OBJ) -o $(NAME)
clean:
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME)
re: fclean all