NAME =  rainbow

S_SRC = rainbow.c  color.c
D_SRC = ./src/
SRC = $(addprefix $(D_SRC), $(S_SRC))

S_OBJ =  $(S_SRC:.c=.o)
D_OBJ = ./obj/
OBJ = $(addprefix $(D_OBJ), $(S_OBJ))

S_INC =  rainbow.h
D_INC = $(D_SRC)
INC = $(addprefix $(D_INC), $(S_INC))

CC =  cc
FLAGS =  -Wall -Wextra -Werror -D_GNU_SOURCE

RM =  rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(FLAGS) $^ -o$@

$(OBJ): $(D_OBJ)%.o:	$(D_SRC)%.c	$(INC)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -I$(D_INC) -c $< -o$@

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(OBJ) $(NAME)

re: fclean
	make all

.PHONY: re fclean clean all $(CC) $(FLAGS) $(RM)
