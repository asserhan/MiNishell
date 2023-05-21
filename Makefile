# Variables
NAME = minishell
CC = cc
FLAGS = -Wall -Werror -Wextra -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include
RM = rm -rf
LIBTFT = libft/libft.a
OBJ_DIR = obj
SRC := $(notdir $(shell find src -name '*.c'))
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
LEAKS =  -g
# Targets
all: $(NAME)

$(NAME): $(OBJ) obj_libft
	@$(CC)  $(FLAGS) $(OBJ) $(LIBTFT)  -lreadline -o $@

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(LEAKS) -c $< -o $@

$(OBJ_DIR)/%.o: src/*/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/*/*/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

obj_libft:
	$(MAKE) -C libft
	@make bonus -C libft

clean:
	$(MAKE) -C libft clean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re obj_libft