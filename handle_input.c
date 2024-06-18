/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:17:04 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/18 17:21:06 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		sl_handle_input(int keysym, t_game *game);
void	sl_player_move(t_game *game, int x, int y, int player_sprite);

int	sl_handle_input(int keysym, t_game *game)
{
	if (keysym == KEY_UP || keysym == KEY_W)
		sl_player_move(game, game->map.position_y - 1, game->map.position_x, BACK);
	if (keysym == KEY_LEFT || keysym == KEY_A)
		sl_player_move(game, game->map.position_y, game->map.position_x - 1, LEFT);
	if (keysym == KEY_RIGHT || keysym == KEY_D)
		sl_player_move(game, game->map.position_y, game->map.position_x + 1, RIGHT);
	if (keysym == KEY_DOWN || keysym == KEY_S)
		sl_player_move(game, game->map.position_y + 1, game->map.position_x, FRONT);
	if (keysym == KEY_ESC)
		sl_close_game(game);
	return (0);
}

void	sl_player_move(t_game *game, int current_y, int current_x, int player_sprite)
{
	int	previous_x;
	int	previous_y;

	game->player_sprite = player_sprite;
	previous_x = game->map.position_x;
	previous_y = game->map.position_y;
	if (game->map.all[current_y][current_x] == EXIT && game->map.coins == 0)
		sl_close_game(game);
	else if ((game->map.all[current_y][current_x] == FLOOR)	|| (game->map.all[current_y][current_x] == COINS))
	{
		game->map.all[previous_y][previous_x] = FLOOR;
		if (game->map.all[current_y][current_x] == COINS)
			game->map.coins--;
		game->map.position_x = current_x;
		game->map.position_y = current_y;
		game->map.all[current_y][current_x] = PLAYER;
		game->movements++;
		sl_render_map(game);
	}
}