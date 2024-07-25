/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:17:04 by dangonz3          #+#    #+#             */
/*   Updated: 2024/07/25 19:42:30 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int		sl_handle_input(int keysym, t_game *game);
void	sl_player_move(t_game *game, int x, int y, int player_sprite);
void	sl_player_move_two(t_game *game, int current_y, \
		int current_x);
void	sl_handle_enemies(t_game *game);

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
	game->game_loop++;
	return (0);
}

void	sl_player_move(t_game *game, int current_y, \
		int current_x, int player_sprite)
{
	game->player_sprite = player_sprite;
	if ((game->map.all[current_y][current_x] == EXIT && \
	game->map.coin_number <= 0) \
	|| game->map.all[current_y][current_x] == ENEMY)
		sl_close_game(game);
	if (game->map.all[current_y][current_x] == WALL \
	|| (game->map.all[current_y][current_x] == \
	EXIT && game->map.coin_number > 0))
		return ;
	sl_player_move_two(game, current_y, current_x);
}

void	sl_player_move_two(t_game *game, int current_y, \
		int current_x)
{
	int	previous_y;
	int	previous_x;

	previous_y = game->map.position_y;
	previous_x = game->map.position_x;
	if (game->map.all[current_y][current_x] == FLOOR \
	|| game->map.all[current_y][current_x] == COIN)
	{
		if (game->map.all[current_y][current_x] == COIN)
			game->map.coin_number--;
		game->map.all[previous_y][previous_x] = FLOOR;
		game->map.all[current_y][current_x] = PLAYER;
		game->movements++;
		game->map.position_x = current_x;
		game->map.position_y = current_y;
		sl_handle_enemies(game);
	}
}

void	sl_handle_enemies(t_game *game)
{
	if (game->map.enemy_number > 0)
		sl_basic_enemy(game);
	sl_render_map(game);
	sl_movement_counter(game);
}
