/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_images.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:44:45 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/27 16:47:26 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void		sl_init_mlx(t_game *game);
void		sl_init_sprites(t_game *game);
t_sprite	sl_new_sprite(char *path, t_game *game);



void	sl_init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		sl_error("ERROR: couldn`t find mlx pointer.\n", game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, \
		game->map.axis_x * IMG_SIZE, game->map.axis_y * IMG_SIZE, "SO_LONG");
	mlx_hook(game->win_ptr, ON_DESTROY, 1L<<17, sl_close_game, (void *)&game);
	if (!game->win_ptr)
		sl_error("ERROR: couldn`t open a window.\n", game);
}

void	sl_init_sprites(t_game *game)
{
	game->wall = sl_new_sprite(WALL_SPRITE, game);
	game->floor = sl_new_sprite(FLOOR_SPRITE, game);
	game->coins = sl_new_sprite(COIN_SPRITE, game);
	game->player_front = sl_new_sprite(PLAYER_SPRITE_FRONT, game);
	game->player_left = sl_new_sprite(PLAYER_SPRITE_LEFT, game);
	game->player_right = sl_new_sprite(PLAYER_SPRITE_RIGHT, game);
	game->player_back = sl_new_sprite(PLAYER_SPRITE_BACK, game);
	game->exit_open = sl_new_sprite(EXIT_OPEN_SPRITE, game);
	game->exit_closed = sl_new_sprite(EXIT_CLOSED_SPRITE, game);
}

t_sprite	sl_new_sprite(char *file, t_game *game)
{
	t_sprite	image;

	image.sprite_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
		file, &image.width, &image.height);
	if (!image.sprite_ptr)
		sl_error("ERROR: couldn't find a sprite.\n", game);
	return (image);
}
