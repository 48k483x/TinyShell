FLAGS = -Wall -Wextra -Werror 
SRC = minishell.c ./utils/split.c ./utils/ft_libft.c \
		./utils/errors.c ./utils/parsing.c ./utils/signals.c

OBJ = $(SRC:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(FLAGS) $(OBJ) -o $(NAME) -lreadline

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ) $(OBJ_BONUS)
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
.SECONDARY: $(OBJ)
