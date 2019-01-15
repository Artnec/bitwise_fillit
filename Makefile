NAME		=	bitwise_fillit

CC			=	clang

FLAGS		=	-O3 -Wall -Werror -Wextra -Wshadow

SRC			=	main.c	fillit.c	parse_and_validate.c

INC			=	fillit.h

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
HEADER		=	$(addprefix $(SRC_DIR), $(INC))

SRC_DIR		=	src/
OBJ_DIR		=	obj/

all: $(NAME)

analyze:
	cppcheck -q --enable=all --inconclusive $(SRC_DIR)

obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | obj
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
