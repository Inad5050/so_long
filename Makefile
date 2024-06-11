# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 09:09:40 by dangonz3          #+#    #+#              #
#    Updated: 2024/06/10 18:21:00 by dangonz3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
CCFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC_DIR = sources/
OBJ_DIR = objects/
SRC_FILES = getting_started
SRC = $(addsuffix .c, $(addprefix sources/, $(SRC_FILES)))
OBJ = $(addsuffix .o, $(addprefix objects/, $(SRC_FILES)))

INCLUDE = -I./includes/

# compilar biblioteca MLX
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L $(MLX_DIR) -lmlx 
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR) -s
	@echo "MESSAGE: MLX compiled"

# compilar biblioteca LIBFT
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L $(LIBFT_DIR) -lft
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR) -s
	@echo "MESSAGE: LIBFT compiled"

# otras bibliotecas
OTHER_FLAGS = -L/usr/lib/X11 -lXext -lX11

# programa
all: $(MLX_LIB) $(LIBFT_LIB)
	@echo "MESSAGE: so_long compiled"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< $(INCLUDE) -o $@

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT_FLAGS) $(OTHER_FLAGS) -o $(NAME)

# funciones adicionales
clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR) -s
	
fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR) -s
	$(MAKE) clean -C $(MLX_DIR) -s

re: fclean all

.PHONY:	all clean fclean re