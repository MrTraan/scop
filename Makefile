NAME = scop

C_DIR = src
C_DIRS = $(shell find $(C_DIR) -type d -follow -print | grep -v '/tests_')
C_FILES = $(shell find $(C_DIRS) -type f -follow -print | grep "\.c" | grep -v '.swp')

O_DIR =	.tmp/obj
O_DIRS = $(C_DIRS:$(C_DIR)%=$(O_DIR)%)
O_FILES = $(C_FILES:$(C_DIR)%.c=$(O_DIR)%.o)

#FLAGS = -Wall -Wextra -Werror
FLAGS = 
INCLUDES = -I ./includes -I ./libft/includes -I /Users/ngrasset/.brew/include/  -I /Users/ngrasset/.brew/include/GLFW
LIB = -L /usr/local/lib -framework OpenGL -framework AppKit -L ./libft -l ft -L /Users/ngrasset/.brew/lib -l GLEW -l glfw

CC = gcc

all: $(NAME)

$(NAME): $(O_FILES)
	make -C libft
	$(CC) $(FLAGS) $^ $(INCLUDES) $(LIB) -o $@

$(O_DIR)%.o: $(C_DIR)%.c
	@mkdir -p $(O_DIRS) $(O_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	make clean -C libft
	@rm -Rf $(O_DIR)

fclean: clean
	make fclean -C libft
	@rm $(NAME) || true
	@rm -Rf .tmp/

debug:
	make -C libft
	$(CC) $(FLAGS) -g $(C_FILES) $(INCLUDES) $(LIB) -o $(NAME)_debug

re: fclean all

.PHONY: clean all fclean re
