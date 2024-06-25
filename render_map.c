/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:44:45 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/24 13:21:30 by dangonz3         ###   ########.fr       */
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
		sl_render_sprite (game, game->wall, y, x);
	else if (parameter == FLOOR)
		sl_render_sprite (game, game->floor, y, x);
	else if (parameter == COINS)
		sl_render_sprite (game, game->coins, y, x);
	else if (parameter == EXIT)
	{
		if (game->map.coins == 0)
			sl_render_sprite (game, game->exit_open, y, x);
		else
			sl_render_sprite (game, game->exit_closed, y, x);
	}
	else if (parameter == PLAYER)
		sl_render_player (game, y, x);
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
		image.sprite_ptr, x * image.width, y * image.width);
}

void	sl_movement_counter(t_game *game)
{
	char	*movements;
	char	*phrase;

	movements = ft_itoa(game->movements);
	phrase = ft_strjoin("Movements : ", movements);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 40, 20, 99999, phrase);
	free(movements);
	free(phrase);
}
/* 
int		mlx_string_put(void *mlx_ptr, void *win_ptr, int x,
		int y, int color, char *string); */