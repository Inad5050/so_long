# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 09:09:40 by dangonz3          #+#    #+#              #
#    Updated: 2024/06/12 12:50:32 by dangonz3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CCFLAGS = -Wall -Wextra -Werror

# Colores
COLOR_GREEN = \033[0;32m
COLOR_RESET = \033[0m

# sources
SRC_DIR = sources/
SRC_FILES = getting_started
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(SRC:.c=.o)

# headers
INCLUDE = -I./includes/

# biblioteca LIBFT
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
	
# biblioteca MLX
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a 
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11
# X11 ya está incluida en el sistema y se encarga de la gestión de la ventana (tiene dos bibliotecas -lXext -lX11),\
la necesitamos para usar MLX

# programa
all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)
	@echo "$(COLOR_GREEN)------------ MESSAGE: PROCESS SUCCESSFULLY FINISHED ------------ $(COLOR_RESET)"

$(NAME): $(OBJ)
	gcc $(CCFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS) $(LIBFT_LIB) $(INCLUDE)
# Always link your external libs AFTER your object files!
# Una vez compiladas las bibliotecas solo tenemos añadir las Flags al proceso de enlace entre los archivos objeto,\
las bibliotecas y los headers

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR) all -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: MLX COMPILED ------------ $(COLOR_RESET)"

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR) all -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: LIBFT COMPILED ------------ $(COLOR_RESET)"

%.o: %.c
	gcc $(CCFLAGS) -c $< -o $@ $(INCLUDE)
	@echo "$(COLOR_GREEN)------------ MESSAGE: SO_LONG COMPILED ------------ $(COLOR_RESET)"
	
# funciones adicionales
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