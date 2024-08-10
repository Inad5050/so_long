/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:26:16 by dangonz3          #+#    #+#             */
/*   Updated: 2024/07/07 20:48:39 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	sl_initiate_enemies(t_game *game);
void	sl_select_basic_enemy(t_game *game);
void	sl_enemy_direction(t_game *game, int i);
void	sl_enemy_direction_alternative(t_game *game, int i);
void	sl_enemy_move(t_game *game, int current_y, int current_x, int i);

void	sl_initiate_enemies(t_game *game)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	game->map.enemy = ft_calloc(game->map.enemy_number, sizeof(t_enemy));
	if (!game->map.enemy)
		sl_error("Couldn't allocate memory for enemies.\n", game);
	while (y < game->map.axis_y && i < game->map.enemy_number)
	{
		x = 0;
		while (x < game->map.axis_x)
		{
			if (game->map.all[y][x] == ENEMY)
			{
				game->map.enemy[i].position_y = y;
				game->map.enemy[i].position_x = x;
				game->map.enemy[i].direction = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	sl_basic_enemy(t_game *game)
{
	int	i;

	i = 0;	
	while(i < game->map.enemy_number)
	{
		if (((50 < game->game_loop && game->game_loop < 100) || \
		(150 < game->game_loop && game->game_loop < 200)) && game->map.boss_b_number > 0)
			sl_enemy_direction_alternative(game, i);
		else
			sl_enemy_direction(game, i);
		i++;
	}
}

void	sl_enemy_direction(t_game *game, int i)
{
	int	current_y;
	int	current_x;
	
	current_y = game->map.enemy[i].position_y;
	current_x = game->map.enemy[i].position_x;
	if (game->map.enemy[i].direction == 0)
		current_x = current_x + 1;
	else if (game->map.enemy[i].direction == 1)
		current_y = current_y + 1;
	else if  (game->map.enemy[i].direction == 2)
		current_x = current_x - 1;
	else if  (game->map.enemy[i].direction == 3)
		current_y = current_y - 1;
	sl_enemy_move(game, current_y, current_x, i);
}

void	sl_enemy_direction_alternative(t_game *game, int i)
{
	int	current_y;
	int	current_x;
	
	current_y = game->map.enemy[i].position_y;
	current_x = game->map.enemy[i].position_x;
	if  (game->map.enemy[i].direction == 0)
		current_x = current_x - 1;
	else if  (game->map.enemy[i].direction == 1)
		current_y = current_y - 1;
	else if (game->map.enemy[i].direction == 2)
		current_x = current_x + 1;
	else if(game->map.enemy[i].direction == 3)
		current_y = current_y + 1;
	sl_enemy_move(game, current_y, current_x, i);
}

void	sl_enemy_move(t_game *game, int current_y, int current_x, int i)
{
	int	previous_y;
	int	previous_x;
	
	previous_y = game->map.enemy[i].position_y;
	previous_x = game->map.enemy[i].position_x;
	if (game->map.all[current_y][current_x] == PLAYER)
		sl_close_game(game);
	else if (game->map.all[current_y][current_x] == WALL \
	|| game->map.all[current_y][current_x] == COIN \
	|| game->map.all[current_y][current_x] == EXIT
	|| game->map.all[current_y][current_x] == ENEMY)
		game->map.enemy[i].direction = (game->map.enemy[i].direction + 1) % 4;
	else if (game->map.all[current_y][current_x] == FLOOR || game->map.all[current_y][current_x] == TERRAIN)
	{
		game->map.all[current_y][current_x] = ENEMY;
		if (game->map.boss_b_number > 0)
			game->map.all[previous_y][previous_x] = TERRAIN;
		else
			game->map.all[previous_y][previous_x] = FLOOR;
		game->map.enemy[i].position_y = current_y;
		game->map.enemy[i].position_x = current_x;
	}
}
