# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 09:09:40 by dangonz3          #+#    #+#              #
#    Updated: 2024/07/25 18:58:57 by dangonz3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME = so_long
NAME = so_long
NAME_BONUS = so_long_bonus
CC = gcc
CCFLAGS = -Wall -Wextra -Werror

# colors
COLOR_GREEN = \033[0;32m
COLOR_RESET = \033[0m

# sources
SRC_DIR = sources/
SRC_DIR_BONUS = sources_bonus/
# SRC_FILES = check_map close_game handle_input initiate_game initiate_map render_map so_long
SRC_FILES = check_map.c check_map_two.c close_game.c close_game_two.c handle_input.c initiate_images.c initiate_game.c render_map.c flood_map.c auxiliars.c main.c
SRC_FILES_BONUS = check_map_bonus.c check_map_two_bonus.c close_game_bonus.c close_game_two_bonus.c handle_input_bonus.c initiate_images_bonus.c initiate_game_bonus.c render_map_bonus.c basic_enemy_bonus.c flood_map_bonus.c auxiliars_bonus.c main_bonus.c
# SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(SRC:.c=.o)
SRC_BONUS = $(addprefix $(SRC_DIR_BONUS), $(SRC_FILES_BONUS))
OBJ_BONUS = $(SRC_BONUS:.c=.o)

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

bonus: $(MLX_LIB) $(LIBFT_LIB) $(NAME_BONUS)
	@echo "$(COLOR_GREEN)------------ PROCESS FINISHED ------------ $(COLOR_RESET)"

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(FLAGS) $(LIBFT_LIB) -o $(NAME) $(INCLUDE)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CCFLAGS) $(OBJ_BONUS) $(FLAGS) $(LIBFT_LIB) -o $(NAME) $(INCLUDE)

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
	rm -f $(OBJ_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"
	
fclean: 
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean -s
	$(MAKE) -C $(MLX_DIR) clean -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"

re: fclean all

rebonus: fclean bonus

.PHONY:	all clean fclean re

#compilar sin MAKEFILE desde /so_long
#gcc -Wall -Werror -Wextra ./sources/*.c ./mlx/libmlx.a ./libft/libft.a -lX11 -lXext -o so_long -g
#./so_long ./maps/map.ber
