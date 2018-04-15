# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/15 18:16:02 by ngrasset          #+#    #+#              #
#    Updated: 2018/04/15 18:17:36 by ngrasset         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop

C_DIR = src
C_FILES = src/errors.c src/file_utils.c src/glad.c src/main.c src/mat4.c \
	src/mat4_2.c src/model.c src/parse_obj_file.c src/shader.c src/shader_setting.c \
	src/texture.c src/view.c

O_DIR =	.tmp/obj
O_FILES = $(C_FILES:$(C_DIR)%.c=$(O_DIR)%.o)

FLAGS = -Wall -Wextra -Werror -O3
INCLUDES = -I ./includes -I./libs -I ./libft/includes -I /Users/ngrasset/.brew/include/  -I /Users/ngrasset/.brew/include/GLFW
LIB = -L /usr/local/lib -framework OpenGL -framework AppKit -L ./libft -l ft -L /Users/ngrasset/.brew/lib -l glfw

CC = clang

all: $(NAME)

$(NAME): $(O_FILES)
	make -C libft
	$(CC) $(FLAGS) $^ $(INCLUDES) $(LIB) -o $@

$(O_DIR)%.o: $(C_DIR)%.c
	@mkdir -p $(O_DIR)
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
