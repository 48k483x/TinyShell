FLAGS = -g -Wall -Wextra -Werror 
SRC = minishell.c ./src/utils/split.c ./src/utils/ft_libft.c \
		./src/utils/errors.c ./src/utils/signals.c \
			./src/parse/check_syntax.c ./src/tools/fd.c ./src/env/env.c ./src/env/get_env.c ./src/env/shlvl.c \
			./src/free/free.c ./src/parse/parse.c ./src/parse/tokens.c \
			./src/tools/token.c ./src/tools/type.c ./src/exec/redir.c

OBJ = $(SRC:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(FLAGS) $(OBJ) -o $(NAME) -lreadline

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
