name = philo

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

SRC = clean_simu.c init.c simulation.c time_manipulation.c fill_struct.c main.c printer.c superviser.c

OBJ = $(SRC:.c=.o)

RM = rm -rf



all: $(name)

$(name) : $(OBJ)
	$(CC) $(OBJ) -o $(name) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(name)

re: fclean all

.PHONY: all clean fclean re
