/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:52:43 by dangonz3          #+#    #+#             */
/*   Updated: 2024/08/02 16:18:08 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

//map elements
# define WALL		'1'
# define FLOOR		'0'
# define COIN		'C'
# define PLAYER		'P'
# define EXIT		'E'
# define ENEMY		'F'

# define IMG_SIZE	64
# define MAX_MOVES	200

//sprites
# define WALL_SPRITE			"./textures/wall.xpm"
# define FLOOR_SPRITE			"./textures/floor.xpm"
# define COIN_SPRITE			"./textures/coin.xpm"
# define PLAYER_SPRITE_FRONT	"./textures/player_down.xpm"
# define PLAYER_SPRITE_LEFT		"./textures/player_left.xpm"
# define PLAYER_SPRITE_RIGHT	"./textures/player_right.xpm"
# define PLAYER_SPRITE_BACK		"./textures/player_up.xpm"
# define EXIT_OPEN_SPRITE		"./textures/exit_opened.xpm"
# define EXIT_CLOSED_SPRITE		"./textures/exit_closed.xpm"
# define ENEMY_SPRITE			"./textures/basic_enemy.xpm"

//player movement
# define FRONT			1
# define LEFT			2
# define RIGHT			3
# define BACK			4

//keys
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100

# define KEY_UP  		65362
# define KEY_LEFT  		65361
# define KEY_RIGHT 		65363
# define KEY_DOWN  		65364

# define KEY_ESC  		65307

//events
# define ON_KEYDOWN		2
# define ON_DESTROY	   	17
# define ON_EXPOSE  	12

//colors
# define COLOR_RED 		"\033[0;31m"
# define COLOR_GREEN 	"\033[0;32m"
# define COLOR_RESET 	"\033[0m"

typedef struct s_sprite
{
	void	*sprite_ptr;
	int		width;
	int		height;
}		t_sprite;

typedef struct s_enemy
{
	int		position_y;
	int		position_x;
	int		direction;
}		t_enemy;

typedef struct s_element
{
	int		position_y;
	int		position_x;
}		t_element;

typedef struct s_map
{
	char		**all;
	int			axis_x;
	int			axis_y;
	int			player_number;
	int			coin_number;
	int			exit_number;
	int			enemy_number;
	int			position_y;
	int			position_x;
	t_element	*element;
	int			element_number;
	int			**flooded;
	t_enemy		*enemy;
}		t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	int			map_bool;
	int			images_bool;
	int			movements;
	int			player_sprite;
	int			game_loop;
	int			ondoor;
	t_sprite	wall_sprite;
	t_sprite	floor_sprite;
	t_sprite	coin_sprite;
	t_sprite	player_front;
	t_sprite	player_left;
	t_sprite	player_right;
	t_sprite	player_back;
	t_sprite	exit_open;
	t_sprite	exit_closed;
	t_sprite	enemy_sprite;
}		t_game;

//initiate_game
void		sl_initiate_game(int argc, char **argv, t_game *game);
void		sl_check_arguments(int argc, char **argv, t_game *game);
void		sl_init_map(t_game *game, char *argv);
void		sl_check_for_empty_line(char *map, t_game *game);
void		sl_init_vars(t_game *game);

//check_map
void		sl_check_map(t_game *game);
void		sl_check_limits(t_game *game);
void		sl_check_rectangular(t_game *game);
void		sl_count_map_elements(t_game *game);
void		sl_sum_map_elements(t_game *game, int y, int x);

//check_map2
void		sl_verify_map_elements(t_game *game);

//flood_map
void		sl_flood_map(t_game *game);
void		sl_initiate_flood(t_game *game);
void		sl_element_finder(t_game *game);
void		sl_floodfill(t_game *game, int x, int y, int index);
void		sl_check_flood(t_game *game);

//initiate_images
void		sl_init_mlx(t_game *game);
void		sl_init_sprites(t_game *game);
t_sprite	sl_new_sprite(char *file, t_game *game);

//render_map
int			sl_render_map(t_game *game);
void		sl_identify_sprite(t_game *game, int y, int x);
void		sl_render_player(t_game *game, int y, int x);
void		sl_render_sprite(t_game *game, t_sprite sprite, \
				int y, int x);
void		sl_movement_counter(t_game *game);

//basic_enemies
void		sl_initiate_enemies(t_game *game);
void		sl_basic_enemy(t_game *game);
void		sl_enemy_direction(t_game *game, int i);
void		sl_enemy_direction_alternative(t_game *game, int i);
void		sl_enemy_move(t_game *game, int current_y, \
		int current_x, int i);

//handle_input
int			sl_handle_input(int keysym, t_game *game);
void		sl_player_move(t_game *game, int x, int y, int player_sprite);
void		sl_player_move_two(t_game *game, int current_y, \
		int current_x);
void		sl_handle_enemies(t_game *game);

//close_game
int			sl_error(char *message, t_game *game);
int			sl_close_game(t_game *game);
void		sl_free_all_allocated_memory(t_game *game);
void		sl_free_map(t_game *game);
void		sl_free_enemies(t_game *game);
void		sl_destroy_images(t_game *game);

//auxiliars
char		*sl_strjoin(char *s1, const char *s2);
int			sl_distance(int a_y, int a_x, int b_y, int b_x);

#endif
