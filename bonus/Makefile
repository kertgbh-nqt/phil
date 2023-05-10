name = philo

CFLAGS = -Wall -Wextra -Werror

SRC = clean_simu_bonus.c init_bonus.c simulation_bonus.c time_manipulation_bonus.c fill_struct_bonus.c main_bonus.c printer_bonus.c superviser_bonus.c

OBJ = clean_simu_bonus.o init_bonus.o simulation_bonus.o time_manipulation_bonus.o fill_struct_bonus.o main_bonus.o printer_bonus.o superviser_bonus.o

RM = rm -rf



all: $(name)

$(name) : $(OBJ)
	$(CC) $(OBJ) -o $(name)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(name)

re: fclean all

.PHONY: all clean fclean re
