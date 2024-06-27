/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:17:04 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/27 15:35:36 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int		sl_handle_input(int keysym, t_game *game);
void	sl_player_move(t_game *game, int x, int y, int player_sprite);

int	sl_handle_input(int keysym, t_game *game)
{
	if (keysym == KEY_ESC)
		sl_close_game(game);
	if (keysym == KEY_UP || keysym == KEY_W)
		sl_player_move(game, game->map.position_y - 1, \
			game->map.position_x, BACK);
	if (keysym == KEY_LEFT || keysym == KEY_A)
		sl_player_move(game, game->map.position_y, \
			game->map.position_x - 1, LEFT);
	if (keysym == KEY_RIGHT || keysym == KEY_D)
		sl_player_move(game, game->map.position_y, \
			game->map.position_x + 1, RIGHT);
	if (keysym == KEY_DOWN || keysym == KEY_S)
		sl_player_move(game, game->map.position_y + 1, \
			game->map.position_x, FRONT);
	return (0);
}

void	sl_player_move(t_game *game, int current_y, \
		int current_x, int player_sprite)
{
	int	previous_x;
	int	previous_y;

	game->player_sprite = player_sprite;
	previous_y = game->map.position_y;
	previous_x = game->map.position_x;
	if (game->map.all[current_y][current_x] == EXIT && game->map.coins <= 0)
		sl_close_game(game);
	if (game->map.all[current_y][current_x] == WALL)
		return ;
	if (game->map.all[current_y][current_x] == FLOOR \
	|| game->map.all[current_y][current_x] == COINS \
	|| game->map.all[current_y][current_x] == EXIT)
	{
		if (game->map.all[current_y][current_x] == COINS)
			game->map.coins--;
		if (game->map.all[current_y][current_x] != EXIT)
			game->map.all[current_y][current_x] = PLAYER;
		if (game->map.all[previous_y][previous_x] != EXIT)
			game->map.all[previous_y][previous_x] = FLOOR;
		game->movements++;
		game->map.position_x = current_x;
		game->map.position_y = current_y;
		sl_render_map(game);
	}
}
