# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 09:09:40 by dangonz3          #+#    #+#              #
#    Updated: 2024/07/07 21:30:38 by dangonz3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = so_long
NAME = so_long
CC = gcc
CCFLAGS = -Wall -Wextra -Werror

# colors
COLOR_GREEN = \033[0;32m
COLOR_RESET = \033[0m

# sources
SRC_DIR = sources/
# SRC_FILES = check_map close_game handle_input initiate_game initiate_map render_map so_long
SRC_FILES = check_map.c check_map2.c close_game.c close_game2.c handle_input.c initiate_images.c initiate_game.c render_map.c basic_enemy.c flood_map.c boss_a.c boss_b.c mimic_enemy.c main.c
# SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(SRC:.c=.o)

# headers
INCLUDE = -I./includes/

# library LIBFT
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
	
# library MLX
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a 
FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
# X11 ya está incluida en el sistema y se encarga de la gestión de la ventana \
(tiene dos bibliotecas -lXext -lX11), la necesitamos para usar MLX
# -lm flags de la biblioteca math.h

# program
all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)
	@echo "$(COLOR_GREEN)------------ PROCESS FINISHED ------------ $(COLOR_RESET)"

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(FLAGS) $(LIBFT_LIB) -o $(NAME) $(INCLUDE)
# Always link your external libs AFTER your object files!
# Una vez compiladas las bibliotecas solo tenemos añadir las Flags al proceso de \
enlace entre los archivos objeto, las bibliotecas y los headers

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR) all -s 2> /dev/null
	@echo "$(COLOR_GREEN)------------ MESSAGE: MLX COMPILED ------------ $(COLOR_RESET)"
# /dev/null para que al compilar la mlx no de mensaje de error

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR) all -s
	
%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@ $(INCLUDE)
	@echo "$(COLOR_GREEN)------------ MESSAGE: $@ COMPILED ------------ $(COLOR_RESET)"
	
# additional functions
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"
	
fclean: 
	rm -f $(OBJ)
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean -s
	$(MAKE) -C $(MLX_DIR) clean -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"

re: fclean all

.PHONY:	all clean fclean re

#compilar sin MAKEFILE desde /so_long
#gcc -Wall -Werror -Wextra ./sources/*.c ./mlx/libmlx.a ./libft/libft.a -lX11 -lXext -o so_long -g
#./so_long ./maps/map.ber
