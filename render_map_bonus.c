/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:44:45 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/30 16:57:33 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int		sl_render_map(t_game *game);
void	sl_identify_sprite(t_game *game, int y, int x);
void	sl_render_player(t_game *game, int y, int x);
void	sl_render_sprite(t_game *game, t_sprite sprite, int y, int x);
void	sl_movement_counter(t_game *game);

int	sl_render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.axis_y)
	{
		x = 0;
		while (x < game->map.axis_x)
		{
			sl_identify_sprite(game, y, x);
			x++;
		}
		y++;
	}
	sl_movement_counter(game);
	return (0);
}

void	sl_identify_sprite(t_game *game, int y, int x)
{
	char	parameter;

	parameter = game->map.all[y][x];
	if (parameter == WALL)
		sl_render_sprite (game, game->wall_sprite, y, x);
	else if (parameter == FLOOR)
		sl_render_sprite (game, game->floor_sprite, y, x);
	else if (parameter == COINS)
		sl_render_sprite (game, game->coin_sprite, y, x);
	else if (parameter == EXIT)
	{
		if (game->map.coin_number == 0)
			sl_render_sprite (game, game->exit_open, y, x);
		else
			sl_render_sprite (game, game->exit_closed, y, x);
	}
	else if (parameter == PLAYER)
		sl_render_player (game, y, x);
	else if (parameter == ENEMY)
		sl_render_sprite (game, game->enemy_sprite, y, x);
}

void	sl_render_player(t_game *game, int y, int x)
{
	if (game->player_sprite == FRONT)
		sl_render_sprite (game, game->player_front, y, x);
	if (game->player_sprite == LEFT)
		sl_render_sprite (game, game->player_left, y, x);
	if (game->player_sprite == RIGHT)
		sl_render_sprite (game, game->player_right, y, x);
	if (game->player_sprite == BACK)
		sl_render_sprite (game, game->player_back, y, x);
}

void	sl_render_sprite(t_game *game, t_sprite image, int y, int x)
{
	mlx_put_image_to_window (game->mlx_ptr, game->win_ptr, \
	image.sprite_ptr, x * IMG_SIZE, y * IMG_SIZE);
}

void	sl_movement_counter(t_game *game)
{
	char	*movements;
	char	*str;

	movements = ft_itoa(game->movements);
	str = ft_strjoin("MOVEMENTS : ", movements);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 30, 30, 0xFFFFFF, str);
	free(movements);
	free(str);
}