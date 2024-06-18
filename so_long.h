/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:52:43 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/18 18:35:26 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdio.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

//map elements
# define WALL		'1'
# define FLOOR		'0'
# define COINS		'C'
# define PLAYER		'P'
# define EXIT		'E'

//sprites
# define WALL_SPRITE			"../assets/wall.xpm"
# define FLOOR_SPRITE			"../assets/floor.xpm"
# define COIN_SPRITE			"../assets/coin.xpm"
# define PLAYER_SPRITE_FRONT	"../assets/player.xpm"
# define PLAYER_SPRITE_LEFT		"../assets/player.xpm"
# define PLAYER_SPRITE_RIGHT	"../assets/player.xpm"
# define PLAYER_SPRITE_BACK		"../assets/player.xpm"
# define EXIT_OPEN_SPRITE		"../assets/exit.xpm"
# define EXIT_CLOSED_SPRITE		"../assets/exit.xpm"

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

typedef struct s_game
{
    void		*mlx_ptr;
    void		*win_ptr;	
    t_map		map;
	int			map_bool;
	int			movements;
	t_sprite	wall;
	t_sprite	floor;
	t_sprite	coins;
	t_sprite	player_front;
	t_sprite	player_left;
	t_sprite	player_right;
	t_sprite	player_back;
	t_sprite	exit_open;
	t_sprite	exit_closed;
	int			player_sprite;
}		t_game;

typedef struct s_map
{   
    char    **all;
    char    *path;
    int     axis_x;
    int     axis_y;
	int		player;
	int		coins;
	int		exit;
	int		initial_position_x;
	int		initial_position_y;
	int		position_x;
	int		position_y;
}		t_map;

typedef struct s_sprite
{
	void	*sprite_ptr;
	int		width;
	int		height;
}		t_sprite;

//initiate_map
void		sl_check_arguments(int argc, char **argv, t_game *game); //(1)
void		sl_initiate_map(t_game *game, char *argv); //(2)
void		sl_check_for_empty_line(char *map, t_game *game); //(2.1)

//initiate_game
void		sl_init_vars(t_game *game); //(3)
void		sl_init_mlx(t_game *game); //(5)
void		sl_init_sprites(t_game *game); //(6)
t_sprite	sl_new_sprite(char *path, t_game *game); //(6.1)

//check_map
void	sl_check_map(t_game *game); //(4)
void	sl_check_rows(t_game *game); //(4.1)
void	sl_check_columns(t_game *game); //(4.2)
void	sl_count_map_elements(t_game *game); //(4.3)
void	sl_verify_map_elements(t_game *game); //(4.4)

//render_map
int			sl_render_map(t_game *game); //(7) REPETEADLY
void		sl_identify_sprite(t_game *game, int y, int x); //(7.1)
void		sl_render_player(t_game *game, int y, int x); //(7.2)
void		sl_render_sprite(t_game *game, t_sprite sprite, int y, int x); //(7.3)
void		sl_movement_counter(t_game *game); //(7.4)

//handle_input
int			sl_handle_input(int keysym, t_game *game); //(8)
void		sl_player_move(t_game *game, int x, int y, int player_sprite); //(8.1)

//close_game
int			sl_close_game(t_game *game); //(9) SOMETIMES (8.1)(8.2)
void		sl_free_all_allocated_memory(t_game *game); //(9.1)
void		sl_destroy_images(t_game *game); //(9.2)
void		sl_free_map(t_game *game); //(9.3)
void		sl_error(char *message, t_game *game); // SOMETIMES check_map initiate_game initiate_map

#endif
