# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anestor <anestor@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/09 19:34:27 by anestor           #+#    #+#              #
#    Updated: 2018/03/07 18:20:42 by anestor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= wolf3d
FLAGS				= -Wall -Wextra -Werror -g
FWORKS				= -framework OpenGL -framework AppKit
MLX					= -L/usr/local/lib -lmlx
OBJ_DIR				= obj/
EXT					= wolf.h

SRC					=
SRC					+= main.c
SRC					+= read_file.c
SRC					+= ray_casting.c
SRC					+= key_hooks.c
SRC					+= render.c
SRC					+= move.c
SRC					+= put_pixels.c

OBJ					= $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC))
.SILENT:

LIBFT_DIR			= libft/
LIBFT_FLAGS			= -L$(LIBFT_DIR) -lft
LIBFT_INC			= -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJ) $(EXT)
	@make -C $(LIBFT_DIR) -j4
	@gcc $(FLAGS) $(LIBFT_FLAGS) $(MLX) $(FWORKS) $(OBJ) -o $(NAME)

obj/%.o: %.c $(EXT)
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS)  -c $< -o $@ $(LIBFT_INC)
	@echo "... compiling $< ..."

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "... cleaning fdf obj ..."

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "... cleaning $(NAME) ..."

re: fclean all

.PHONY: clean fclean re all test
